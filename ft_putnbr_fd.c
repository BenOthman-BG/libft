/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 16:16:33 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 10:49:25 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_number(long n, int fd)
{
	if (n > 9)
		ft_write_number(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	a;

	a = n;
	if ( a < 0)
	{
		write(fd, "-", 1);
		a = (-1) * a;
	}
	ft_write_number(a, fd);
}
