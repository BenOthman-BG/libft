/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 18:05:50 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/15 18:55:11 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

/* ---------------------------------------------------- */
/* 1. النسخة الصحيحة المطابقة لـ Man (Unsigned)         */
/* ---------------------------------------------------- */
void	*ft_memset_unsigned(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/* ---------------------------------------------------- */
/* 2. النسخة الخاطئة المرفوضة في 42 (Signed)            */
/* ---------------------------------------------------- */
void	*ft_memset_signed(void *s, int c, size_t n)
{
	char	*p;
	size_t	i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (char)c; // هنا يقع الفخ
		i++;
	}
	return (s);
}

/* ---------------------------------------------------- */
/*                      دالة الـ Main                   */
/* ---------------------------------------------------- */
int main(void)
{
	char	buffer1[5];
	char	buffer2[5];
	int		target_value = 200; // قيمة أكبر من 127

	printf("=== Testing memset with value: %d ===\n\n", target_value);

	ft_memset_unsigned(buffer1, target_value, 4);
	printf("[1] Unsigned memset (The Correct Way):\n");
	printf(" - Value compiler assigned : %d\n", (unsigned char)target_value);
	printf(" - Hex value in memory     : %X\n\n", (unsigned char)buffer1[0]);

	ft_memset_signed(buffer2, target_value, 4);
	printf("[2] Signed memset (The Wrong Way):\n");
	printf(" - Value compiler assigned : %d  <-- (Disaster! It became negative)\n", (char)target_value);
	printf(" - Hex value in memory     : %X\n\n", (unsigned char)buffer2[0]);

	printf("=== The Sign Extension Disaster ===\n");
	
	int read_correct = (unsigned char)buffer1[0];
	int read_wrong = (char)buffer2[0];

	printf("If read natively as Unsigned : %d  (Perfect!)\n", read_correct);
	printf("If read natively as Signed   : %d  (Corrupted data!)\n", read_wrong);

	return (0);
}
