/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 19:02:06 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/17 19:44:28 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*p;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	printf("%d\n", (int)(len_s1 + len_s2 + 1));
	p = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[i - len_s1] != '\0')
	{
		p[i] = s2[i - len_s1];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int main (int ac, char **av)
{
	if (ac == 3)
	{
		char *p;

		p = ft_strjoin(av[1], av[2]);
		if (p == NULL)
		{
			printf("NULL\n");
			return (0);
		}
		if (p[0] == '\0')
			printf("end\n");
		else
			printf("%s\n", p);
		free(p);
	}
	return (0);
}
