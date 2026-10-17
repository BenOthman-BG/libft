/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 15:12:07 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/14 17:40:17 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_p;
	const unsigned char	*src_p;

	dest_p = (unsigned char *)dest;
	src_p = (const unsigned char *)src;
	if (dest_p == NULL && src_p == NULL)
		return (dest);
	while (n > 0)
	{
		*dest_p = *src_p;
		dest_p++;
		src_p++;
		n--;
	}
	return (dest);
}
