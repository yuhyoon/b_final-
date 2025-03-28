/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:59:28 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 10:00:49 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_dir(char *exe_path)
{
	struct stat	st;
	int			flg;

	if (exe_path == NULL)
		return (-1);
	flg = stat(exe_path, &st);
	if (flg == -1)
	{
		err_such(127, exe_path);
		return (-1);
	}
	else if (st.st_nlink > 1)
	{
		err_permission(126, exe_path);
		return (1);
	}
	return (0);
}

void	*valid_exepath(t_child_process *child, t_ready *rdy, t_minish *sh)
{
	child->exe_path = get_exepath(rdy, sh);
	if (child->exe_path == NULL)
		err_exec(127, child->cmd[0]);
	if (is_dir(child->exe_path) == 0)
		rdy = access_exepath(child, rdy);
	else
		rdy = NULL;
	if (rdy != NULL)
		child->state = STATE_EXEC_CMD;
	return (rdy);
}

void	init_child_process(t_child_process *child, int *pp, \
t_ready *rdy, t_minish *sh)
{
	child->num = rdy->num;
	child->pp = pp;
	child->cmd = rdy->cmd;
	child->input_fd = rdy->input;
	child->output_fd = rdy->output;
	child->exe_path = NULL;
	child->bulitin_code = is_builtin(child->cmd[0]);
	if (rdy->rdrct != NULL)
		child->state = STATE_CHECK_RDRCT;
	else if (sh->cmd_count > 1)
	{
		child->state = STATE_CHECK_PIPE;
	}
	else if (child->bulitin_code > 0)
		child->state = STATE_EXEC_BUILTIN;
	else
		child->state = STATE_CHECK_CMD;
}

void	*valid_redirect(t_child_process *child, t_ready *rdy, t_minish *sh)
{
	int	v;

	v = find_rdrct(rdy);
	if (v == 0)
	{
		redirect(rdy);
		if (prmssn_rdrct(rdy->rdrct_in) != 0 \
			|| prmssn_rdrct(rdy->rdrct_out) != 0)
			rdy = NULL;
		else
		{
			redirect_input(child, rdy);
			redirect_output(child, rdy);
			if (sh->cmd_count > 1)
				child->state = STATE_CHECK_PIPE;
			else if (child->bulitin_code > 0)
				child->state = STATE_EXEC_BUILTIN;
			else
				child->state = STATE_CHECK_CMD;
		}
	}
	else
		rdy = NULL;
	return (rdy);
}

int	child_process(t_ready *rdy, int *pp, t_minish *sh)
{
	t_child_process	child;

	init_child_process(&child, pp, rdy, sh);
	while (rdy != NULL && child.state < STATE_COMPLETE)
	{
		if (child.state == STATE_CHECK_RDRCT)
			rdy = valid_redirect(&child, rdy, sh);
		else if (child.state == STATE_CHECK_CMD)
			rdy = valid_exepath(&child, rdy, sh);
		else if (child.state == STATE_EXEC_BUILTIN)
			execute_bulitin(&child, sh, rdy);
		else if (child.state == STATE_CHECK_PIPE)
			set_pipe(&child, sh);
		else if (child.state == STATE_EXEC_CMD)
			execute_cmd(&child, sh);
	}
	if (child.state == STATE_CHECK_RDRCT || child.state == STATE_CHECK_PIPE)
		close_pp(&child, sh);
	return (*f_exitcode());
}
