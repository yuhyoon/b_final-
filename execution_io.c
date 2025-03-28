/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.gyeongsan>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:58:54 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 08:59:42 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child_process.h"
#include "execution.h"
#include "error.h"

void	close_pp(t_child_process *child, t_minish *sh)
{
	if (child->bulitin_code > 0)
	{
		if (child->state == STATE_COMPLETE && child->num == sh->cmd_count)
			close(child->input_fd);
	}
	if (child->bulitin_code == 0 && child->num < sh->cmd_count \
		&& child->state == STATE_CHECK_RDRCT \
		|| child->state == STATE_CHECK_PIPE)
	{
		close(child->pp[0]);
		close(child->pp[1]);
	}
}

void	set_pipe(t_child_process *child, t_minish *sh)
{
	if (sh->prev_for_pipe != -1)
	{
		dup2(sh->prev_for_pipe, child->input_fd);
		close(sh->prev_for_pipe);
	}
	if (child->num < sh->cmd_count && sh->cmd_count > 1)
	{
		printf("dup2\n");
		dup2(child->pp[1], child->output_fd);
		close(child->pp[1]);
		close(child->pp[0]);
	}
	if (child->bulitin_code > 0)
	{
		printf("builtin\n");
		child->state = STATE_EXEC_BUILTIN;
	}
	else
		child->state = STATE_CHECK_CMD;
}

void	redirect_input(t_child_process *child, t_ready *rdy)
{
	if (rdy->rdrct_in)
	{
		dup2(rdy->rdrct_in->fd, child->input_fd);
		child->input_fd = rdy->rdrct_in->fd;
		close(rdy->rdrct_in->fd);
	}
}

void	redirect_output(t_child_process *child, t_ready *rdy)
{
	if (rdy->rdrct_out)
	{
		dup2(rdy->rdrct_out->fd, child->output_fd);
		child->output_fd = rdy->rdrct_out->fd;
		close(rdy->rdrct_out->fd);
	}
}
