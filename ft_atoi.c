/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:44:00 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 13:44:06 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		signe;
	long	number;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	signe = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - 48;
		str++;
	}
	return ((int)(signe * number));
}
