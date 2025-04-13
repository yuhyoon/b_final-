/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:58:51 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_io(t_stack *in, t_stack *out, t_ready *rdy)
{
	t_list		*tmp;
	t_redrct	*rd;
	int			n;

	n = rdy->rdrct_num;
	tmp = rdy->rdrct;
	while (n)
	{
		rd = (t_redrct *)(tmp)->content;
		if (rd->type == IN_RD)
			push(in, rd);
		else if (rd->type == OUT_RD)
			queue(out, rd);
		n--;
		tmp = (tmp)->next;
	}
}

void	set_io(t_ready *rdy, t_stack *in, t_stack *out)
{
	(rdy)->rdrct_in = (t_redrct *)pop2(in);
	if (rdy->rdrct_in)
	{
		if (rdy->rdrct_in->parts == 1)
			rdy->rdrct_in->fd = open(rdy->rdrct_in->obj, O_RDONLY);
	}
	while (out->top)
	{
		(rdy)->rdrct_out = (t_redrct *)dequeue(out);
		if (rdy->rdrct_out)
		{
			if (rdy->rdrct_out->parts == 1)
				rdy->rdrct_out->fd = open(rdy->rdrct_out->obj, \
				O_TRUNC | O_WRONLY | O_CREAT, 0644);
			else if (rdy->rdrct_out->parts == 2)
				rdy->rdrct_out->fd = open(rdy->rdrct_out->obj, \
				O_APPEND | O_WRONLY | O_CREAT, 0644);
		}
	}
}

int	prmssn_rdrct(t_redrct *rdrct)
{
	int	flg;

	flg = 0;
	if (rdrct == NULL)
		return (flg);
	if (rdrct->type == IN_RD && rdrct->parts == 1)
		flg = access(rdrct->obj, R_OK);
	else if (rdrct->type == OUT_RD && rdrct->parts == 2)
		flg = access(rdrct->obj, W_OK);
	if (flg != 0)
		err_permission(1, rdrct->obj);
	return (flg);
}

int	find_rdrct(t_ready *rdy)
{
	t_list		*lst;
	t_redrct	*rdrct;
	int			n;
	int			acc_flg;

	lst = rdy->rdrct;
	errno = 0;
	n = rdy->rdrct_num;
	acc_flg = 0;
	while (n && acc_flg == 0)
	{
		rdrct = (t_redrct *)(lst->content);
		if (rdrct->type == IN_RD && rdrct->parts == 1)
			acc_flg = access(rdrct->obj, F_OK);
		lst = lst->next;
		n--;
	}
	if (acc_flg != 0)
		err_such(1, rdrct->obj);
	return (acc_flg);
}

int	redirect(t_ready *rdy)
{
	t_stack	in;
	t_stack	out;

	if (rdy == NULL)
		return (-1);
	init_stack(&in, NULL, 0);
	init_stack(&out, NULL, 0);
	sort_io(&in, &out, rdy);
	set_io(rdy, &in, &out);
	del_stack(&in);
	del_stack(&out);
	return (0);
}
