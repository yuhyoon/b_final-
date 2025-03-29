/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:05:44 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/29 11:05:10 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exit_err_msg(char *copy_str, int code)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
	if (copy_str)
	{
		ft_putstr_fd(copy_str, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
	}
	if (code == 1)
		ft_putstr_fd("too many arguments\n", STDOUT_FILENO);
	else if (code == 2)
		ft_putstr_fd("numeric argument required\n", STDOUT_FILENO);
	exit(code);
}

long long	check_exit_cmd(char *second_cmd)
{
	long long	code;
	char		*tmp;

	code = check_input_range(second_cmd);
	tmp = second_cmd;
	if (second_cmd[0] == '-')
		return (4);
	while (*tmp)
	{
		if (ft_isalnum(*tmp) != 4)
			break ;
		tmp++;
	}
	if (*tmp != '\0')
		code = 2;
	return (code);
}

void	f_exit_only(int exitcode, t_minish *sh)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_all_envps(sh);
	exit(exitcode);
}

void	f_exit_with_msg(int size, char *second_cmd, t_minish *sh)
{
	int	code;

	code = check_exit_cmd(second_cmd);
	if (size == 2)
	{
		if (code == -1)
			exit_err_msg(second_cmd, STDERR_FILENO);
		else
			f_exit_only(code, sh);
	}
	else if (size > 2)
	{
		if (code == -1)
			exit_err_msg(second_cmd, 2);
		else
			exit_err_msg(NULL, 1);
	}
}

int	f_exit(t_minish *sh, t_ready *rdy)
{
	char	**cmds;
	int		size;

	cmds = ((t_ready *)sh->ready->content)->cmd;
	size = f_count_char(cmds);
	if (size == 1)
		f_exit_only(*f_exitcode(), sh);
	else if (size > 1)
		f_exit_with_msg(size, cmds[1], sh);
	return (0);
}
