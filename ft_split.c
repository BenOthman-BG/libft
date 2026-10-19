/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 06:49:37 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/19 11:29:06 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s == '\0')
			return (len);
		len++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (len);
}

static char	*get_word(char const *s, char c, int *pass)
{
	int		len;
	char	*p;
	int		i;

	len = 0;
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i + len] != '\0' && s[i + len] != c)
		len++;
	*pass = i + len;
	p = ft_substr(s, (unsigned int)i, len);
	return (p);
}

static char	**free_split(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		pass;
	int		len;

	if (s == NULL)
		return (NULL);
	len = get_len(s, c);
	arr = malloc ((len + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = get_word(s, c, &pass);
		if (arr[i] == NULL)
			return (free_split(arr, i));
		s = s + pass;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
/*int main (int ac, char **av)
{
	if (ac == 3)
	{
		char **p;
		
		p = ft_split(av[1], av[2][0]);
		if (p == NULL)
		{
			printf("NULL\n");
			return(0);
		}
		while (*p != NULL)
		{
			printf("%s\n", *p);
			p++;
		}
		printf("NULLend\n");
		
	}
	return (0);
}*/
