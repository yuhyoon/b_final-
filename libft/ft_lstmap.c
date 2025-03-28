/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:26:20 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/25 17:46:19 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current_head;
	t_list	*current;

	if (!lst)
		return (0);
	current = ft_lstnew(f(lst));
	if (!current)
	{
		free(current);
		return (0);
	}	
	current_head = current;
	while (lst != NULL)
	{
		lst = lst->next;
		current->next = ft_lstnew(f(lst));
		if (!(current->next))
		{
			ft_lstclear(&current_head, del);
			return (0);
		}
		current = current->next;
	}
	return (current_head);
}
