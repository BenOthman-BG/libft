/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:46:11 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/18 10:39:59 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <bsd/string.h>

int main ()
{
	char *p;
	//char *q;
	
	p = ft_strnstr((void*)0, "fake", 3);
	//q = strnstr((void*)0, "fake", 0);
	if (p == NULL)
		printf("NULL\n");
	else 
		printf("ft_strnstr : %s\n", p);
	free(p);
	/*if (q == NULL)
		printf("NULL\n");
	else
		printf("strnstr : %s\n", q);
	free(q);*/
	return (0);
}
