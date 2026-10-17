/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:50:18 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/17 19:01:46 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include "stdio.h"

static void	fill(char const *s, unsigned int start, size_t len, char *p)
{
	size_t	i;

	i = 0;
	while (s[i + start] != '\0' && i < len)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	len_t;

	if (s == NULL)
		return (NULL);
	len_t = ft_strlen(s);
	if (start >= len_t)
	{
		p = malloc(1 * sizeof(char));
		if (p == NULL)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	if (len > len_t - start)
		len = len_t - start;
	p = malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	fill(s, start, len, p);
	return (p);
}
/*int main ()
{
	char *p;

	p = ft_substr("hello world", 4, 9000);
	if (p == NULL)
		printf("NULL\n");
	else
	{
		if (p[0] == '\0')
			printf("end\n");
		else
			printf("%s\n", p);
	}
	return (0);
}*/
