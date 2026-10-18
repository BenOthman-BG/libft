/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 11:44:57 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/18 11:50:22 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	put(char const *s1, char const *s2, char *p, size_t len_s1)
{
	size_t	i;

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
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	put(s1, s2, p, len_s1);
	return (p);
}

/*int main (int ac, char **av)
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
}*/
