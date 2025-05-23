/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:52:02 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_text(void *txt)
{
	free((char *)txt);
	txt = NULL;
}

void	del_redrct(void *rd)
{
	t_redrct	*redrct;

	if (rd == NULL)
		return ;
	redrct = (t_redrct *)rd;
	if (redrct->type == IN_RD && redrct->parts == 2)
		close(redrct->fd);
	free(redrct->obj);
	redrct->obj = NULL;
	free(redrct);
}

void	del_ready(void *ready)
{
	t_ready	*rdy;

	rdy = ready;
	if (rdy == NULL)
		return ;
	if (rdy->submsk)
		free(rdy->submsk);
	if (rdy->subsrc)
		free(rdy->subsrc);
	if (rdy->newsrc)
		free(rdy->newsrc);
	ft_lstclear(&rdy->rdrct, del_redrct);
	free_str_array(rdy->cmd);
	free(rdy);
	rdy = NULL;
}

void	del_stack(void *st)
{
	t_stack	*stack;

	stack = st;
	if (stack == NULL)
		return ;
	while (!is_emthy(stack))
		pop2(stack);
	stack = NULL;
}
