/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:52:19 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/15 16:17:44 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

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

int main (int ac, char **av)
{
	if (ac == 2)
	printf("ft_atoi : %d\n", ft_atoi(av[1]));
	printf("atoi : %d\n", atoi(av[1]));
}
