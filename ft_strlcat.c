/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:43:09 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/30 09:17:36 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_s;
	size_t	src_s;
	size_t	i;

	dst_s = 0;
	while (dst_s < size && dst[dst_s] != '\0')
		dst_s++;
	src_s = ft_strlen(src);
	if (dst_s >= size)
		return (size + src_s);
	i = 0;
	while ((dst_s + i) < (size - 1) && src[i] != '\0')
	{
		dst[dst_s + i] = src[i];
		i++;
	}
	dst[dst_s + i] = '\0';
	return (dst_s + src_s);
}
