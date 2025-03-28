/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:58:37 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/26 13:50:21 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "main.h"

typedef struct s_child_process	t_child_process;

//execute
int		execute(t_minish *sh);
void	wait_childs(t_minish *sh);
int		execute_single_builtin(int bulitin_code, t_minish *sh);
int		execute_single_is_builtin(t_list *lst, t_minish *sh);

//utils
char	**create_str_2(t_list **head);
void	free_splited(char **abs);

//redirect
int		find_rdrct(t_ready *rdy);
int		prmssn_rdrct(t_redrct *rdrct);
int		redirect(t_ready *rdy);
void	set_io(t_ready *rdy, t_stack *in, t_stack *out);
void	sort_io(t_stack *in, t_stack *out, t_ready *rdy);
void	redirect_input_b(t_ready *rdy, int *io);
void	redirect_output_b(t_ready *rdy, int *io);

//pipe
void	set_pipe(t_child_process *child, t_minish *sh);
void	redirect_input(t_child_process *child, t_ready *rdy);
void	redirect_output(t_child_process *child, t_ready *rdy);
void	close_pp(t_child_process *child, t_minish *sh);

//cmd
char	*get_exepath(t_ready *rdy, t_minish *sh);
char	*find_exepath(char *name, t_minish *sh);
void	*access_exepath(t_child_process *child, t_ready *rdy);
void	execute_cmd(t_child_process *child, t_minish *sh);

//builtin
int		is_builtin(char *cmd_name);
#endif
