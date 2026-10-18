/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 11:58:59 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/18 13:52:56 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static char	*start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, (int)s1[i]) == NULL)
			return ((char *)&s1[i]);
		i++;
	}
	return ((char *)s1);
}

static char	*end(char const *s1, char const *set, size_t len_s1)
{
	size_t	i;

	i = len_s1 - 1;
	while (i != 0)
	{
		if (ft_strchr(set, (int)s1[i]) == NULL)
			return ((char *)&s1[i]);
		i--;
	}
	return ((char *)&s1[len_s1 - 1]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start_p;
	char	*end_p;
	char	*p;
	size_t	len_s1;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	start_p = start(s1, set);
	end_p = end(s1, set, len_s1);
	printf("%ld\n", start_p - end_p);
	if (start_p > end_p)
		p = malloc ((1) * sizeof(char));
	else
		p = malloc ((end_p - start_p + 2) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (start_p <= end_p)
	{
		printf("%d", 0);
		p[i] = *start_p;
		i++;
		start_p++;
	}
	p[i] = '\0';
	return (p);
}

int main (int ac, char **av)
{
	if (ac == 3)
	{
		char *p;

		p = ft_strtrim(av[1], av[2]);
		if (p == NULL)
			printf("NULL\n");
		else
			printf("%s\n", p);
		free(p);
	}
	return (0);
}
