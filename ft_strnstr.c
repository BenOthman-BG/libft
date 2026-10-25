/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:43:37 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 13:43:39 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	size_t	i;

	n_len = ft_strlen(needle);
	i = 0;
	if (n_len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if ((i + n_len) <= len && !ft_strncmp(&haystack[i], needle, n_len))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
