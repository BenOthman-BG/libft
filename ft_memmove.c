/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:36:14 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 13:36:16 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_p;
	const unsigned char	*src_p;

	dest_p = (unsigned char *)dest;
	src_p = (const unsigned char *)src;
	if (dest_p == NULL && src_p == NULL)
		return (dest);
	if (dest_p > src_p)
	{
		while (n > 0)
		{
			dest_p[n -1] = src_p[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
