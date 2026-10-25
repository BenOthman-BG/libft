/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:46:11 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/25 12:33:39 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	my_del(void *content)
{
	printf("[Expert]: I am destroying content -> %s\n", (char *)content);
	free(content);
}

void	*upper(void *s)
{
	char *old_str;
	char *new_str;
	int i;

	if(!s)
		return (NULL);
	
	old_str = (char *)s;
	new_str = ft_strdup(old_str);
	if (!new_str)
		return (NULL);
	i = 0;
	while (new_str[i])
	{
		if (new_str[i] >= 'a' && new_str[i] <= 'z')
			new_str[i] = new_str[i] - 32;
		else if (new_str[i] >= 'A' && new_str[i] <= 'Z')
			new_str[i] = new_str[i] + 32;
		i++;
	}
	return ((void *)new_str);
}

int main ()
{
	t_list	*header;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*node4;
	t_list	*current;
	t_list	*get_last;
	t_list	*header2;

	header = NULL;
	
	node1 = ft_lstnew(ft_strdup("OTHman"));
	node2 = ft_lstnew(ft_strdup("benyHYA"));
	node3 = ft_lstnew(ft_strdup("He"));
	node4 = ft_lstnew(ft_strdup("bACk"));

	if (!node1 || !node2 || !node3)
	{
		printf("NULL\n");
		return (1);
	}

	ft_lstadd_back(&header, node1);
	ft_lstadd_front(&header, node2);
	ft_lstadd_front(&header, node3);
	ft_lstadd_back(&header, node4);

	current = header;
	while (current != NULL)
	{
		printf("node content : %s\n", (char *)current->content);
		current = current->next;
	}

	printf("len = %d\n", ft_lstsize(header));
	get_last = ft_lstlast(header);
	printf("last node content : %s\n", (char *)get_last->content);
	printf("-------------------------------------");
	header2 = ft_lstmap(header, upper, my_del);
	current = header2;

	while (current != NULL)
	{
		printf("new node content : %s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&header, my_del);
	ft_lstclear(&header2, my_del);

	return (0);
}
