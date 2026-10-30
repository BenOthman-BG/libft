/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:45:56 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/30 10:17:43 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
