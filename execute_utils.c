/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.gyeongsan>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:33:12 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/26 14:47:58 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	redirect_input_b(t_ready *rdy, int *io)
{
	int	save_in;

	io[0] = STDIN_FILENO;
	if (rdy->rdrct_in)
	{
		save_in = dup(STDIN_FILENO);
		dup2(rdy->rdrct_in->fd, STDIN_FILENO);
		rdy->input = rdy->rdrct_in->fd;
		io[0] = save_in;
		close(rdy->rdrct_in->fd);
	}
}

void	redirect_output_b(t_ready *rdy, int *io)
{
	int			save_out;
	t_list		*lst;
	t_redrct	*rdrct;

	io[1] = STDOUT_FILENO;
	if (rdy->rdrct_out)
	{
		save_out = dup(STDOUT_FILENO);
		dup2(rdy->rdrct_out->fd, STDOUT_FILENO);
		rdy->output = rdy->rdrct_out->fd;
		io[1] = save_out;
	}
	lst = rdy->rdrct;
	while (lst)
	{
		rdrct = (t_redrct *)(lst->content);
		if (rdrct && rdrct->fd > 2)
			close(rdrct->fd);
		lst = lst->next;
	}
}

void	*valid_redirect_builtin(t_ready *rdy, t_minish *sh)
{
	int		v;
	t_ready	*flg;
	int		save_io[2];

	v = find_rdrct(rdy);
	flg = rdy;
	if (v == 0)
	{
		redirect(rdy);
		if (prmssn_rdrct(rdy->rdrct_in) != 0 || \
			prmssn_rdrct(rdy->rdrct_out) != 0)
			flg = NULL;
		else
		{
			redirect_input_b(rdy, save_io);
			redirect_output_b(rdy, save_io);
		}
		ft_memset(save_io, 0, 2);
		sh->save_in = save_io[0];
		sh->save_out = save_io[1];
	}
	else
		flg = NULL;
	return (flg);
}
