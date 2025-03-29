/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:54:52 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/29 10:50:05 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = new;
		return ;
	}
	if (new == NULL)
		return ;
	while (tmp)
	{
		if ((tmp)->next == NULL)
			break ;
		tmp = (tmp)->next;
	}
	tmp->next = new;
}
