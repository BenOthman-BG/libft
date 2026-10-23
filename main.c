/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:46:11 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/23 20:08:25 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int main ()
{
	t_list	*header;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*current;

	header = NULL;
	
	node1 = ft_lstnew((void *)"othman");
	node2 = ft_lstnew((void *)"benyahy");
	node3 = ft_lstnew((void *)"he");

	if (!node1 || !node2 || !node3)
	{
		printf("NULL\n");
		return (1);
	}

	ft_lstadd_front(&header, node1);
	ft_lstadd_front(&header, node2);
	ft_lstadd_front(&header, node3);

	current = header;
	while (current != NULL)
	{
		printf("node content : %s\n", (char *)current->content);
		current = current->next;
	}
	printf("len = %d\n", ft_lstsize(header));
	free(node3);
	free(node2);
	free(node1);

	return (0);
}
