/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 16:21:10 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/13 16:22:55 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*   main.c - "moulinette-like" hard tester for libft (Part 1: libc funcs)    */
/*                                                                            */
/*   Every function runs in its own forked child: a segfault, abort or        */
/*   infinite loop in one function never stops the other tests.               */
/*   Each ft_ function is compared against the real libc behaviour.           */
/*   (strlcpy / strlcat / strnstr use reference versions written below,       */
/*    so you do NOT need -lbsd.)                                              */
/*                                                                            */
/*   This file is NOT submitted and does NOT need to follow the Norm.         */
/*                                                                            */
/*   Build (recommended, with sanitizers):                                    */
/*     cc -g -fsanitize=address,undefined -I. main.c ft_*.c -o test_libft     */
/*   Build (against your library):                                            */
/*     make && cc -g -I. main.c libft.a -o test_libft                         */
/*   Run:                                                                     */
/*     ./test_libft              -> everything                                */
/*     ./test_libft strlcat atoi -> only these functions                      */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <ctype.h>
#include <limits.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"

#define MAX_MSG 6
#define GUARD 16
#define GBYTE 0xA5
#define RED "\033[31m"
#define GRN "\033[32m"
#define YEL "\033[33m"
#define RST "\033[0m"

static int	g_fails;

#define CHECK(cond, ...) \
	do { \
		if (!(cond)) \
		{ \
			g_fails++; \
			if (g_fails <= MAX_MSG) \
			{ \
				printf("      " RED "x" RST " (line %d) ", __LINE__); \
				printf(__VA_ARGS__); \
				printf("\n"); \
				fflush(stdout); \
			} \
		} \
	} while (0)

#define SGN(x) (((x) > 0) - ((x) < 0))

/* ---------------------------------------------------------------- helpers */

static const char	*shown(const void *v, size_t n)
{
	static char			bufs[4][512];
	static int			k;
	char				*o;
	const unsigned char	*s;
	size_t				i;
	size_t				j;

	o = bufs[k++ & 3];
	s = v;
	j = 0;
	o[j++] = '"';
	for (i = 0; i < n && j < 440; i++)
	{
		if (s[i] == '"' || s[i] == '\\')
		{
			o[j++] = '\\';
			o[j++] = (char)s[i];
		}
		else if (s[i] >= 32 && s[i] < 127)
			o[j++] = (char)s[i];
		else
			j += (size_t)snprintf(o + j, 8, "\\x%02x", (unsigned)s[i]);
	}
	if (i < n)
	{
		o[j++] = '.';
		o[j++] = '.';
		o[j++] = '.';
	}
	o[j++] = '"';
	o[j] = '\0';
	return (o);
}

static const char	*show(const char *s)
{
	return (shown(s, strlen(s)));
}

static char	*xdup(const char *s)
{
	size_t	n;
	char	*r;

	n = strlen(s) + 1;
	r = malloc(n);
	if (!r)
		exit(2);
	memcpy(r, s, n);
	return (r);
}

static void	*xmemdup(const void *s, size_t n)
{
	void	*r;

	r = malloc(n ? n : 1);
	if (!r)
		exit(2);
	if (n)
		memcpy(r, s, n);
	return (r);
}

static long	off(const void *p, const void *base)
{
	if (!p)
		return (-1L);
	return ((long)((const char *)p - (const char *)base));
}

/* guarded buffer: n usable bytes surrounded by GUARD canary bytes */
typedef struct s_gbuf
{
	unsigned char	*base;
	unsigned char	*p;
	size_t			n;
}	t_gbuf;

static t_gbuf	gb_new(size_t n, int fill)
{
	t_gbuf	g;

	g.base = malloc(n + 2 * GUARD);
	if (!g.base)
		exit(2);
	memset(g.base, GBYTE, n + 2 * GUARD);
	g.p = g.base + GUARD;
	g.n = n;
	memset(g.p, fill, n);
	return (g);
}

static int	gb_ok(const t_gbuf *g)
{
	size_t	i;

	for (i = 0; i < GUARD; i++)
		if (g->base[i] != GBYTE || g->p[g->n + i] != GBYTE)
			return (0);
	return (1);
}

static void	gb_free(t_gbuf *g)
{
	free(g->base);
}

/* reference implementations of the BSD functions (glibc may lack them) */
static size_t	ref_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	sl;

	i = 0;
	sl = strlen(src);
	if (size)
	{
		while (i + 1 < size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (sl);
}

static size_t	ref_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	dl = 0;
	while (dl < size && dst[dl])
		dl++;
	sl = strlen(src);
	if (dl == size)
		return (size + sl);
	i = 0;
	while (src[i] && dl + i + 1 < size)
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return (dl + sl);
}

static char	*ref_strnstr(const char *h, const char *n, size_t len)
{
	size_t	nl;
	size_t	i;

	nl = strlen(n);
	if (!nl)
		return ((char *)h);
	for (i = 0; h[i] && i + nl <= len; i++)
		if (!strncmp(h + i, n, nl))
			return ((char *)h + i);
	return (NULL);
}

/* ------------------------------------------------------ ctype functions */

#define CTYPE_TEST(fn, lo, hi) \
	static void test_##fn(void) \
	{ \
		int	c; \
		int	e; \
		int	r; \
		for (c = (lo); c <= (hi); c++) \
		{ \
			e = !!fn(c); \
			r = ft_##fn(c); \
			CHECK(r == e, #fn "(%d): libc=%d ft=%d (must be exactly 0 or 1)", \
				c, e, r); \
		} \
	}

CTYPE_TEST(isalpha, -1, 255)
CTYPE_TEST(isdigit, -1, 255)
CTYPE_TEST(isalnum, -1, 255)
CTYPE_TEST(isascii, -5, 300)
CTYPE_TEST(isprint, -1, 255)

static void	test_toupper(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(ft_toupper(c) == toupper(c), "toupper(%d): libc=%d ft=%d",
			c, toupper(c), ft_toupper(c));
}

static void	test_tolower(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(ft_tolower(c) == tolower(c), "tolower(%d): libc=%d ft=%d",
			c, tolower(c), ft_tolower(c));
}

/* ------------------------------------------------------ string / memory */

static void	test_strlen(void)
{
	const char	*strs[] = {"", "a", "ab", "hello", "hello world", "\xff\x80",
		"tab\there", NULL};
	const char	emb[] = "abc\0def";
	size_t		i;
	size_t		n;
	char		*s;

	for (i = 0; strs[i]; i++)
	{
		s = xdup(strs[i]);
		CHECK(ft_strlen(s) == strlen(s), "strlen(%s): libc=%zu ft=%zu",
			show(s), strlen(s), ft_strlen(s));
		free(s);
	}
	for (n = 0; n <= 300; n++)
	{
		s = malloc(n + 1);
		memset(s, 'z', n);
		s[n] = '\0';
		CHECK(ft_strlen(s) == n, "strlen of %zu 'z': ft=%zu", n, ft_strlen(s));
		free(s);
	}
	CHECK(ft_strlen(emb) == 3, "strlen must stop at first NUL, got %zu",
		ft_strlen(emb));
	s = malloc((1 << 20) + 1);
	memset(s, 'q', 1 << 20);
	s[1 << 20] = '\0';
	CHECK(ft_strlen(s) == (size_t)1 << 20, "strlen of 1MB string wrong");
	free(s);
}

static void	test_memset(void)
{
	int		vals[] = {0, 1, 42, 127, 128, 255, 256, 257, -1, -129, 0x1234,
		INT_MAX, INT_MIN};
	size_t	n;
	size_t	o;
	size_t	v;
	t_gbuf	a;
	t_gbuf	b;
	void	*r;

	for (n = 0; n <= 70; n++)
		for (o = 0; o < 8; o++)
			for (v = 0; v < sizeof vals / sizeof *vals; v++)
			{
				a = gb_new(n + 16, 0x55);
				b = gb_new(n + 16, 0x55);
				r = ft_memset(a.p + o, vals[v], n);
				memset(b.p + o, vals[v], n);
				CHECK(r == a.p + o, "n=%zu off=%zu: wrong return value", n, o);
				CHECK(memcmp(a.p, b.p, a.n) == 0,
					"n=%zu off=%zu c=%d: wrong content", n, o, vals[v]);
				CHECK(gb_ok(&a), "n=%zu off=%zu: wrote out of bounds", n, o);
				gb_free(&a);
				gb_free(&b);
			}
	a = gb_new(1 << 20, 0x11);
	b = gb_new(1 << 20, 0x11);
	ft_memset(a.p, 0xAB, a.n);
	memset(b.p, 0xAB, b.n);
	CHECK(memcmp(a.p, b.p, a.n) == 0, "1MB memset wrong");
	CHECK(gb_ok(&a), "1MB memset out of bounds");
	gb_free(&a);
	gb_free(&b);
}

static void	test_bzero(void)
{
	size_t	n;
	size_t	o;
	t_gbuf	a;
	t_gbuf	b;

	for (n = 0; n <= 70; n++)
		for (o = 0; o < 8; o++)
		{
			a = gb_new(n + 16, 0x55);
			b = gb_new(n + 16, 0x55);
			ft_bzero(a.p + o, n);
			bzero(b.p + o, n);
			CHECK(memcmp(a.p, b.p, a.n) == 0, "n=%zu off=%zu: wrong content",
				n, o);
			CHECK(gb_ok(&a), "n=%zu off=%zu: wrote out of bounds", n, o);
			gb_free(&a);
			gb_free(&b);
		}
}

static void	test_memcpy(void)
{
	size_t			n;
	size_t			so;
	size_t			d;
	size_t			i;
	t_gbuf			s;
	t_gbuf			d1;
	t_gbuf			d2;
	unsigned char	*scopy;
	void			*r;

	for (n = 0; n <= 70; n++)
		for (so = 0; so < 8; so++)
			for (d = 0; d < 8; d++)
			{
				s = gb_new(n + 16, 0);
				d1 = gb_new(n + 16, 0x55);
				d2 = gb_new(n + 16, 0x55);
				for (i = 0; i < s.n; i++)
					s.p[i] = (unsigned char)(i * 7 + 3);
				scopy = xmemdup(s.p, s.n);
				r = ft_memcpy(d1.p + d, s.p + so, n);
				memcpy(d2.p + d, s.p + so, n);
				CHECK(r == d1.p + d, "n=%zu: wrong return value", n);
				CHECK(memcmp(d1.p, d2.p, d1.n) == 0,
					"n=%zu src_off=%zu dst_off=%zu: wrong content", n, so, d);
				CHECK(memcmp(s.p, scopy, s.n) == 0, "n=%zu: src modified", n);
				CHECK(gb_ok(&d1), "n=%zu: wrote out of bounds", n);
				free(scopy);
				gb_free(&s);
				gb_free(&d1);
				gb_free(&d2);
			}
	s = gb_new(1 << 20, 0);
	d1 = gb_new(1 << 20, 0);
	d2 = gb_new(1 << 20, 0);
	for (i = 0; i < s.n; i++)
		s.p[i] = (unsigned char)(i * 13 + 1);
	ft_memcpy(d1.p, s.p, s.n);
	memcpy(d2.p, s.p, s.n);
	CHECK(memcmp(d1.p, d2.p, s.n) == 0, "1MB memcpy wrong");
	gb_free(&s);
	gb_free(&d1);
	gb_free(&d2);
}

static void	test_memmove(void)
{
	size_t			ns[] = {0, 1, 2, 3, 7, 8, 9, 15, 16, 17, 31, 32, 33, 63, 64};
	size_t			k;
	size_t			so;
	size_t			d;
	size_t			i;
	unsigned char	a[128];
	unsigned char	b[128];
	void			*r;

	for (k = 0; k < sizeof ns / sizeof *ns; k++)
		for (so = 0; so <= 40; so++)
			for (d = 0; d <= 40; d++)
			{
				for (i = 0; i < 128; i++)
				{
					a[i] = (unsigned char)(i * 5 + 1);
					b[i] = a[i];
				}
				r = ft_memmove(a + d, a + so, ns[k]);
				memmove(b + d, b + so, ns[k]);
				CHECK(r == a + d, "n=%zu: wrong return value", ns[k]);
				CHECK(memcmp(a, b, 128) == 0,
					"overlap n=%zu src=+%zu dst=+%zu: wrong content "
					"(forward/backward copy?)", ns[k], so, d);
			}
}

static void	test_strlcpy(void)
{
	const char	*srcs[] = {"", "a", "ab", "hello", "hello world",
		"0123456789012345678901234567890123456789", NULL};
	size_t		i;
	size_t		sz;
	char		*src;
	t_gbuf		a;
	t_gbuf		b;
	size_t		ra;
	size_t		rb;

	for (i = 0; srcs[i]; i++)
		for (sz = 0; sz <= 45; sz++)
		{
			src = xdup(srcs[i]);
			a = gb_new(sz, 'X');
			b = gb_new(sz, 'X');
			ra = ft_strlcpy((char *)a.p, src, sz);
			rb = ref_strlcpy((char *)b.p, src, sz);
			CHECK(ra == rb, "strlcpy(src=%s, size=%zu): return exp=%zu got=%zu",
				show(src), sz, rb, ra);
			CHECK(memcmp(a.p, b.p, sz) == 0,
				"strlcpy(src=%s, size=%zu): dst exp=%s got=%s "
				"(must NUL-terminate and not touch bytes after the NUL)",
				show(src), sz, shown(b.p, sz), shown(a.p, sz));
			CHECK(gb_ok(&a), "strlcpy(src=%s, size=%zu): wrote out of bounds",
				show(src), sz);
			free(src);
			gb_free(&a);
			gb_free(&b);
		}
}

static void	test_strlcat(void)
{
	const char	*dsts[] = {"", "a", "abc", "hello", "0123456789", NULL};
	const char	*srcs[] = {"", "x", "world", "0123456789abcdef", NULL};
	size_t		i;
	size_t		j;
	size_t		sz;
	size_t		dl;
	size_t		bs;
	char		*src;
	t_gbuf		a;
	t_gbuf		b;
	size_t		ra;
	size_t		rb;

	for (i = 0; dsts[i]; i++)
		for (j = 0; srcs[j]; j++)
			for (sz = 0; sz <= 30; sz++)
			{
				dl = strlen(dsts[i]);
				bs = sz > dl + 1 ? sz : dl + 1;
				src = xdup(srcs[j]);
				a = gb_new(bs, 'X');
				b = gb_new(bs, 'X');
				memcpy(a.p, dsts[i], dl + 1);
				memcpy(b.p, dsts[i], dl + 1);
				ra = ft_strlcat((char *)a.p, src, sz);
				rb = ref_strlcat((char *)b.p, src, sz);
				CHECK(ra == rb,
					"strlcat(dst=%s, src=%s, size=%zu): return exp=%zu got=%zu",
					show(dsts[i]), show(src), sz, rb, ra);
				CHECK(memcmp(a.p, b.p, bs) == 0,
					"strlcat(dst=%s, src=%s, size=%zu): dst exp=%s got=%s",
					show(dsts[i]), show(src), sz, shown(b.p, bs),
					shown(a.p, bs));
				CHECK(gb_ok(&a), "strlcat(dst=%s, src=%s, size=%zu): "
					"wrote out of bounds", show(dsts[i]), show(src), sz);
				free(src);
				gb_free(&a);
				gb_free(&b);
			}
}

static void	test_strchr(void)
{
	const char	*strs[] = {"", "a", "abc", "hello world", "aaaa", "abcabcabc",
		"\xff\x80zz\x7f", "tripouille", NULL};
	int			c;
	size_t		i;
	char		*s;
	char		*a;
	char		*b;

	for (i = 0; strs[i]; i++)
	{
		s = xdup(strs[i]);
		for (c = -300; c <= 600; c++)
		{
			a = ft_strchr(s, c);
			b = strchr(s, c);
			CHECK(a == b, "strchr(%s, %d): expected offset %ld, got %ld",
				show(s), c, off(b, s), off(a, s));
		}
		free(s);
	}
}

static void	test_strrchr(void)
{
	const char	*strs[] = {"", "a", "abc", "hello world", "aaaa", "abcabcabc",
		"\xff\x80zz\x7f", "tripouille", NULL};
	int			c;
	size_t		i;
	char		*s;
	char		*a;
	char		*b;

	for (i = 0; strs[i]; i++)
	{
		s = xdup(strs[i]);
		for (c = -300; c <= 600; c++)
		{
			a = ft_strrchr(s, c);
			b = strrchr(s, c);
			CHECK(a == b, "strrchr(%s, %d): expected offset %ld, got %ld",
				show(s), c, off(b, s), off(a, s));
		}
		free(s);
	}
}

static void	test_strncmp(void)
{
	static const char	*p[][2] = {{"", ""}, {"", "a"}, {"a", ""},
	{"abc", "abc"}, {"abc", "abd"}, {"abd", "abc"}, {"abc", "ab"},
	{"ab", "abc"}, {"abcdef", "abcdeg"}, {"\x80", "\x7f"}, {"\x7f", "\x80"},
	{"\xff", "\x01"}, {"test\x80", "test"}, {"test", "test\x80"}, {"A", "a"},
	{"zz", "zz"}, {"hello world", "hello there"}, {NULL, NULL}};
	size_t				ns[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, SIZE_MAX};
	char				e1[] = "abc\0def";
	char				e2[] = "abc\0xyz";
	size_t				i;
	size_t				k;
	char				*a;
	char				*b;
	int					ra;
	int					rb;

	for (i = 0; p[i][0]; i++)
	{
		a = xdup(p[i][0]);
		b = xdup(p[i][1]);
		for (k = 0; k < sizeof ns / sizeof *ns; k++)
		{
			ra = ft_strncmp(a, b, ns[k]);
			rb = strncmp(a, b, ns[k]);
			CHECK(SGN(ra) == SGN(rb),
				"strncmp(%s, %s, %zu): libc sign=%d ft=%d (unsigned char "
				"comparison, stop at NUL)", show(a), show(b), ns[k],
				SGN(rb), ra);
		}
		free(a);
		free(b);
	}
	CHECK(ft_strncmp(e1, e2, 7) == 0, "strncmp must stop at the first NUL");
}

static void	test_memchr(void)
{
	enum {L = 100};
	unsigned char	base[L];
	unsigned char	*buf;
	int				c;
	size_t			n;
	size_t			i;
	void			*a;
	void			*b;

	for (i = 0; i < L; i++)
		base[i] = (unsigned char)(i * 37 + 5);
	for (n = 0; n <= L; n++)
	{
		buf = xmemdup(base, n);
		for (c = -2; c <= 520; c++)
		{
			a = ft_memchr(buf, c, n);
			b = memchr(buf, c, n);
			CHECK(a == b, "memchr(base, %d, %zu): expected offset %ld, got %ld",
				c, n, off(b, buf), off(a, buf));
		}
		free(buf);
	}
	for (n = 1; n <= 20; n++)
	{
		buf = malloc(n);
		for (i = 0; i < n; i++)
			buf[i] = (i % 2) ? 'y' : 'x';
		a = ft_memchr(buf, 'y', n);
		b = memchr(buf, 'y', n);
		CHECK(a == b, "memchr(xyxy..., 'y', %zu): must return FIRST match", n);
		a = ft_memchr(buf, 'x', n);
		b = memchr(buf, 'x', n);
		CHECK(a == b, "memchr(xyxy..., 'x', %zu): must return FIRST match", n);
		free(buf);
	}
}

static void	test_memcmp(void)
{
	static const unsigned char	vals[] = {0x00, 0x01, 0x7f, 0x80, 0xff};
	unsigned char				base[64];
	unsigned char				*a;
	unsigned char				*b;
	size_t						n;
	size_t						k;
	size_t						v;
	size_t						i;
	int							ra;
	int							rb;

	for (i = 0; i < 64; i++)
		base[i] = (unsigned char)(i * 37);
	for (n = 0; n <= 64; n++)
		for (k = 0; k <= n; k++)
			for (v = 0; v < sizeof vals; v++)
			{
				a = xmemdup(base, n);
				b = xmemdup(base, n);
				if (k < n)
					b[k] = vals[v];
				ra = ft_memcmp(a, b, n);
				rb = memcmp(a, b, n);
				CHECK(SGN(ra) == SGN(rb),
					"memcmp n=%zu diff at %zu (byte 0x%02x vs 0x%02x): "
					"libc sign=%d ft=%d", n, k, a[k < n ? k : 0],
					vals[v], SGN(rb), ra);
				free(a);
				free(b);
			}
	CHECK(ft_memcmp("a\0b", "a\0c", 3) < 0, "memcmp must not stop at NUL (<)");
	CHECK(ft_memcmp("a\0c", "a\0b", 3) > 0, "memcmp must not stop at NUL (>)");
	CHECK(ft_memcmp("a\0b", "a\0c", 2) == 0, "memcmp n=2 must ignore byte 3");
	CHECK(ft_memcmp("\x80", "\x7f", 1) > 0, "memcmp must use unsigned bytes");
	CHECK(ft_memcmp("\x7f", "\x80", 1) < 0, "memcmp must use unsigned bytes");
}

static void	test_strnstr(void)
{
	static const char	*p[][2] = {{"", ""}, {"", "a"}, {"abc", ""},
	{"abc", "abc"}, {"abc", "abcd"}, {"abcdef", "def"}, {"abcdef", "cde"},
	{"abcdef", "f"}, {"abcdef", "a"}, {"aaabaaab", "aab"},
	{"aaaaaa", "aaab"}, {"hello world", "o w"}, {"hello", "lo"},
	{"mississippi", "issip"}, {"mississippi", "pi"}, {"abcabcabd", "abd"},
	{"lorem ipsum dolor sit amet", "dolor"},
	{"lorem ipsum dolor sit amet", "ipsumm"}, {"abc", "c"}, {"abc", "bc"},
	{"a", "a"}, {"a", "b"}, {NULL, NULL}};
	size_t				i;
	size_t				len;
	size_t				hl;
	char				*h;
	char				*nd;
	char				*a;
	char				*b;

	for (i = 0; p[i][0]; i++)
	{
		hl = strlen(p[i][0]);
		h = xdup(p[i][0]);
		nd = xdup(p[i][1]);
		for (len = 0; len <= hl + 3; len++)
		{
			a = ft_strnstr(h, nd, len);
			b = ref_strnstr(h, nd, len);
			CHECK(a == b, "strnstr(%s, %s, %zu): expected offset %ld, got %ld",
				show(h), show(nd), len, off(b, h), off(a, h));
		}
		a = ft_strnstr(h, nd, SIZE_MAX);
		b = ref_strnstr(h, nd, SIZE_MAX);
		CHECK(a == b, "strnstr(%s, %s, SIZE_MAX): expected offset %ld, got %ld",
			show(h), show(nd), off(b, h), off(a, h));
		free(h);
		free(nd);
	}
}

static void	test_atoi(void)
{
	const char	*strs[] = {"0", "1", "-1", "+1", "42", "-42", "+42", "   42",
		"\t\n\v\f\r 42", " \t-42", "--42", "++42", "+-42", "-+42", "42abc",
		"abc42", "", "-", "+", " ", "  -", "0042", "-0042", "2147483647",
		"-2147483648", "+2147483647", "00000000000000000000042", "42 42",
		"4 2", "- 42", " +0", "-0", "1e5", "0x1A", "\x1b 42", "12345678",
		"-12345678", "999999999", "-999999999", "2147483647abc",
		"\n\n\n  -2147483648  ", NULL};
	size_t		i;
	char		*s;

	for (i = 0; strs[i]; i++)
	{
		s = xdup(strs[i]);
		CHECK(ft_atoi(s) == atoi(s), "atoi(%s): libc=%d ft=%d", show(s),
			atoi(s), ft_atoi(s));
		free(s);
	}
}

static void	test_calloc(void)
{
	static const size_t	t[][2] = {{0, 0}, {0, 5}, {5, 0}, {1, 1}, {10, 1},
	{1, 10}, {3, 7}, {7, 3}, {100, 100}, {1000, 1000}, {1, 100000},
	{65536, 4}};
	static const size_t	ov[][2] = {{SIZE_MAX, 2}, {2, SIZE_MAX},
	{SIZE_MAX / 2 + 1, 2}, {SIZE_MAX, SIZE_MAX}, {SIZE_MAX / 3 + 1, 3}};
	size_t				i;
	size_t				k;
	size_t				sz;
	void				*d;
	unsigned char		*p;
	void				*a;
	void				*b;

	for (i = 0; i < sizeof t / sizeof *t; i++)
	{
		sz = t[i][0] * t[i][1];
		d = malloc(sz ? sz : 1);
		memset(d, 0xAA, sz ? sz : 1);
		free(d);
		p = ft_calloc(t[i][0], t[i][1]);
		CHECK(p != NULL, "calloc(%zu, %zu) returned NULL (must return a "
			"unique pointer passable to free())", t[i][0], t[i][1]);
		if (!p)
			continue ;
		for (k = 0; k < sz; k++)
			if (p[k])
			{
				CHECK(0, "calloc(%zu, %zu): byte %zu is not zero",
					t[i][0], t[i][1], k);
				break ;
			}
		memset(p, 0x42, sz);
		free(p);
	}
	a = ft_calloc(0, 0);
	b = ft_calloc(0, 0);
	CHECK(a != NULL && b != NULL && a != b,
		"calloc(0, 0) must return distinct non-NULL pointers");
	free(a);
	free(b);
	for (i = 0; i < sizeof ov / sizeof *ov; i++)
	{
		a = ft_calloc(ov[i][0], ov[i][1]);
		CHECK(a == NULL, "calloc(%zu, %zu): multiplication overflow must "
			"return NULL", ov[i][0], ov[i][1]);
		free(a);
	}
}

static void	test_strdup(void)
{
	const char	*strs[] = {"", "a", "hello", "hello world", "\xff\x80 end",
		"tab\tnl\n", NULL};
	size_t		i;
	char		*src;
	char		*r;
	char		*big;

	for (i = 0; strs[i]; i++)
	{
		src = xdup(strs[i]);
		r = ft_strdup(src);
		CHECK(r != NULL, "strdup(%s) returned NULL", show(src));
		if (r)
		{
	#include "libft.h"
#include <stdio.h>

int main (int ac, char **av)
{
	if (ac == 2)
	{
		printf("%d\n", ft_isalnum(av[1][0]));
	}
	return (0);
}
		CHECK(r != src, "strdup(%s) returned the same pointer", show(src));
			CHECK(strcmp(r, src) == 0, "strdup(%s): got %s", show(src),
				show(r));
			r[0] = (char)(r[0] + 1);
			CHECK(strcmp(src, strs[i]) == 0, "modifying the copy changed the "
				"source");
		}
		free(r);
		free(src);
	}
	big = malloc(100001);
	memset(big, 'k', 100000);
	big[100000] = '\0';
	r = ft_strdup(big);
	CHECK(r && strcmp(r, big) == 0, "strdup of 100000 chars wrong");
	free(r);
	free(big);
}

/* ------------------------------------------------------------------ main */

typedef struct s_test
{
	const char	*name;
	void		(*fn)(void);
}	t_test;

static int	g_total;
static int	g_ok;

static void	run(const t_test *t)
{
	int		fd[2];
	pid_t	pid;
	int		st;
	char	out[16384];
	size_t	len;
	ssize_t	r;
	int		sig;

	len = 0;
	if (pipe(fd) < 0)
		exit(2);
	fflush(stdout);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		alarm(10);
		g_fails = 0;
		t->fn();
		if (g_fails > MAX_MSG)
			printf("      ... and %d more failure(s)\n", g_fails - MAX_MSG);
		fflush(stdout);
		exit(g_fails ? 1 : 0);
	}
	close(fd[1]);
	while ((r = read(fd[0], out + len, sizeof out - 1 - len)) > 0)
		len += (size_t)r;
	close(fd[0]);
	out[len] = '\0';
	waitpid(pid, &st, 0);
	g_total++;
	if (WIFEXITED(st) && WEXITSTATUS(st) == 0)
	{
		g_ok++;
		printf(GRN "[ OK  ]" RST " ft_%s\n", t->name);
		return ;
	}
	if (WIFEXITED(st))
		printf(RED "[ KO  ]" RST " ft_%s%s\n", t->name, out[0] ? ""
			: "  (no message: check stderr, sanitizer/leak report?)");
	else
	{
		sig = WTERMSIG(st);
		printf(RED "[CRASH]" RST " ft_%s  -> %s\n", t->name,
			sig == SIGSEGV ? "SEGFAULT" : sig == SIGBUS ? "BUS ERROR"
			: sig == SIGABRT ? "ABORT (double free / invalid free?)"
			: sig == SIGALRM ? "TIMEOUT (infinite loop?)" : "killed by signal");
	}
	printf("%s", out);
}

int	main(int argc, char **argv)
{
	static const t_test	tests[] = {
	{"isalpha", test_isalpha}, {"isdigit", test_isdigit},
	{"isalnum", test_isalnum}, {"isascii", test_isascii},
	{"isprint", test_isprint}, {"strlen", test_strlen},
	{"memset", test_memset}, {"bzero", test_bzero},
	{"memcpy", test_memcpy}, {"memmove", test_memmove},
	{"strlcpy", test_strlcpy}, {"strlcat", test_strlcat},
	{"toupper", test_toupper}, {"tolower", test_tolower},
	{"strchr", test_strchr}, {"strrchr", test_strrchr},
	{"strncmp", test_strncmp}, {"memchr", test_memchr},
	{"memcmp", test_memcmp}, {"strnstr", test_strnstr},
	{"atoi", test_atoi}, {"calloc", test_calloc},
	{"strdup", test_strdup}};
	size_t				i;
	int					a;
	int					want;

	printf(YEL "=== libft - Part 1 (libc functions) hard tester ===" RST "\n");
	for (i = 0; i < sizeof tests / sizeof *tests; i++)
	{
		want = (argc == 1);
		for (a = 1; a < argc; a++)
			if (!strcmp(argv[a], tests[i].name)
				|| (!strncmp(argv[a], "ft_", 3)
					&& !strcmp(argv[a] + 3, tests[i].name)))
				want = 1;
		if (want)
			run(&tests[i]);
	}
	printf(YEL "=== %d/%d functions passed ===" RST "\n", g_ok, g_total);
	return (g_ok != g_total);
}