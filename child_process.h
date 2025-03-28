/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:58:28 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/27 11:21:09 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_PROCESS_H
# define CHILD_PROCESS_H


# include "main.h"
# include "execution.h"
# include "error.h"

typedef enum s_child_state
{
	STATE_CHECK_RDRCT = 1,
	STATE_EXEC_BUILTIN,
	STATE_CHECK_CMD = 127,
	STATE_CHECK_PIPE,
	STATE_EXEC_CMD,
	STATE_COMPLETE
}t_child_state;

typedef struct s_child_process
{
	int				num;
	t_child_state	state;
	int				*pp;
	char			**cmd;
	char			*exe_path;
	int				input_fd;
	int				output_fd;
	int				bulitin_code;
}t_child_process;

int			child_process(t_ready *rdy, int *pp, t_minish *sh);
//void		execute_cmd(t_child_process *child);
//void		set_pipe(t_child_process *child, t_minish *sh, t_ready *rdy);
void		*valid_redirect(t_child_process *child, t_ready *rdy, t_minish *sh);
//int		prmssn_rdrct(t_redrct *rdrct);
void		init_child_process(t_child_process *child, int *pp, t_ready *rdy, t_minish *sh);
//void		*valid_exepath(t_child_process *child, t_ready *rdy, t_minish *sh);
//void		close_pp(t_child_process *child, t_minish *sh);
//int		is_builtin(char *cmd_name);

int			execute_bulitin(t_child_process *child, t_minish *sh, t_ready *rdy);
// int			execute_builtin(t_child_process *child, t_minish *sh, t_ready* rdy);

#endif
