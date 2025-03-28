/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:48 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/25 17:39:54 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	cnt;
	t_list	*tmp;

	tmp = lst;
	cnt = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		cnt++;
	}
	return (cnt);
}
