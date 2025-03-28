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

#include "child_process.h"
#include "execution.h"
#include "free.h"
#include "signals.h"

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
	int	save_out;

	io[1] = STDOUT_FILENO;
	if (rdy->rdrct_out)
	{
		save_out = dup(STDOUT_FILENO);
		dup2(rdy->rdrct_out->fd, STDOUT_FILENO);
		rdy->output = rdy->rdrct_out->fd;
		io[1] = save_out;
		close(rdy->rdrct_out->fd);
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

void	wait_childs(t_minish *sh)
{
	int	i;
	int	status;
	int w;

	i = 0;
	while (sh->child_pids != NULL && i < sh->cmd_count)
	{
		waitpid(sh->child_pids[i], &status, 0);
		if (i == sh->cmd_count - 1)
		{
			*f_exitcode() = WEXITSTATUS(status);
			set_signal(before_readline);
		}
		i++;
	}
}

int close_redirec_b(t_minish *sh)
{
	if (sh->save_in != STDIN_FILENO)
	{
		dup2(sh->save_in, STDIN_FILENO);
		close(sh->save_in);
		sh->save_in = STDIN_FILENO;
	}
	if (sh->save_out != STDOUT_FILENO)
	{
		dup2(sh->save_out, STDOUT_FILENO);
		close(sh->save_out);
		sh->save_out = STDOUT_FILENO;
	}
	return (0);
}

int	execute_single_builtin(int bulitin_code, t_minish *sh)
{
	int		res;
	t_ready	*rdy;

	res = -1;
	rdy = (t_ready *)(sh->ready->content);
	if (valid_redirect_builtin(rdy, sh) == NULL)
		return (-1);
	if (bulitin_code == 1)
		res = f_cd(sh);
	else if (bulitin_code == 2)
		res = f_echo(sh, rdy);
	else if (bulitin_code == 3)
		res = f_pwd(rdy);
	else if (bulitin_code == 4)
		res = f_export(sh);
	else if (bulitin_code == 5)
		res = f_env(sh);
	else if (bulitin_code == 6)
		res = f_unset(sh);
	else if (bulitin_code == 7)
		res = f_exit(sh, rdy);
	close_redirec_b(sh);
	return (res);
}

int	execute_single_is_builtin(t_list *lst, t_minish *sh)
{
	t_ready	*rdy;
	int		bulitin_code;
	int		result;

	rdy = (t_ready *)(lst->content);
	if (rdy->cmd[0] == NULL)
		return (-1);
	bulitin_code = is_builtin(rdy->cmd[0]);
	result = bulitin_code;
	if (bulitin_code != 0)
	{
		result = execute_single_builtin(bulitin_code, sh);
		if (result == 0)
			result = bulitin_code;
		else
			result = -1;
	}
	return (result);

}

int	execute(t_minish *sh)
{
	t_list		*lst;
	t_ready		*rdy;
	int			n;

	sh->cmd_count = ft_lstsize(sh->ready);
	lst = sh->ready;
	set_signal(before_readline);
	rdy = (t_ready *)(lst->content);
	n = is_builtin(rdy->cmd[0]);
	if (n > 0 && sh->cmd_count == 1)
			execute_single_is_builtin(lst, sh);
	else
	{
		sh->child_pids = ft_calloc(sizeof(pid_t), sh->cmd_count);
		while (lst)
		{
			rdy = (t_ready *)(lst->content);
			create_process(rdy, sh);

			lst = lst->next;
		}
		wait_childs(sh);
	}
	free_minish(sh);
	return (0);
}
