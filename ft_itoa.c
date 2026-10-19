/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:45:59 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/19 15:03:45 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	get_len(int n)
{
	if (n / 10 == 0)
	{
		if (n < 0)
			return (2);
		return (1);
	}
	return (1 + get_len(n / 10));
}

static void	putstr(char *s, long number, int categorie)
{
	while (categorie >= 1)
	{
		*s = number / categorie + '0';
		number = number % categorie;
		categorie = categorie / 10;
		s++;
	}
	*s = '\0';
}

static void	getstr(char *s, int n, int len)
{
	long	number;
	int		categorie;
	int		i;

	number = n;
	if (n < 0)
	{
		*s = '-';
		s++;
		len--;
		number = number * (-1);
	}
	i = 1;
	categorie = 1;
	while (i < len)
	{
		categorie = categorie * 10;
		i++;
	}
	putstr(s, number, categorie);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		len;

	len = get_len(n);
	p = malloc ((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	getstr(p, n, len);
	return (p);
}

int main ()
{
	printf("%s\n", ft_itoa(-201));
	return (0);
}
