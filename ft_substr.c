/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 11:52:21 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/30 10:01:29 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	len_t;

	if (s == NULL)
		return (NULL);
	len_t = ft_strlen(s);
	if (start >= len_t)
		return (ft_strdup(""));
	if (len > len_t - start)
		len = len_t - start;
	p = malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s + start, len + 1);
	return (p);
}
