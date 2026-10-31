/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:43:37 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/30 10:22:24 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n_len;
	size_t	i;

	n_len = ft_strlen(little);
	i = 0;
	if (n_len == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] != '\0' && len >= i + n_len)
	{
		if (big[i] == little[0] && !ft_strncmp(&big[i], little, n_len))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}