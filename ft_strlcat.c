/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:43:09 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 13:43:14 by obenyahy         ###   ########.fr       */
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
	src_s = (size_t)ft_strlen(src);
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

/*size_t	ft_strcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	dst_len = ft_strlen(dst);
	printf("%ld\n", dst_len);
	if (size <= dst_len)
		return (dst_len + src_len);
	while (src[i] && i < (size - dst_len - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}*/

/*#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

// [Insert your ft_strlcat and ft_strlen here]

int main(void)
{

	char *dest;
	char *ref;

	dest = malloc (5 * sizeof(char));
	dest[0] = 'a';
	dest[1] = 'b';
	dest[2] = 'b';
	dest[3] = 'b';
	dest[4] = 'b';
	dest[5] = 'b';
	dest[6] = 'b';
	dest[7] = 'b';
	dest[8] = 'b';
	dest[9] = 'b';
	dest[10] = 'b';
	dest[11] = 'b';
	dest[12] = '\0';

	printf("yassin : %d\n", (int)ft_strcat(dest, "othman", 5));
	free(ref);
    return 0;
}*/
