/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:41:41 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 13:41:44 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	c = (char)c;
	while (len >= 0)
	{
		if (s[len] == c)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}
