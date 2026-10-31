/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenyahy <obenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 11:13:17 by obenyahy          #+#    #+#             */
/*   Updated: 2026/10/27 19:53:43 by obenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*header;
	t_list	*node;
	void	*content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	header = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (node == NULL)
		{
			if (content != NULL)
				del(content);
			ft_lstclear(&header, del);
			return (NULL);
		}
		ft_lstadd_back(&header, node);
		lst = lst->next;
	}
	return (header);
}
