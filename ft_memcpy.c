/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:35:29 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 13:35:32 by obenyahy         ###   ########.fr       */
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
