/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:05:44 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/06 14:41:04 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exit_err_msg(char *copy_str, int code, t_minish *sh)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
	if (copy_str)
	{
		ft_putstr_fd(copy_str, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
	}
	if (code == -1)
	{
		*f_exitcode() = 1;
		ft_putstr_fd("too many arguments\n", STDOUT_FILENO);
	}
	else if (code == -2)
	{
		*f_exitcode() = 255;
		ft_putstr_fd("numeric argument required\n", STDOUT_FILENO);
	}
	else
		*f_exitcode() = code;
	free_all_envps(sh);
	free_minish(sh);
	exit(*f_exitcode());
}

int	check_number_or_not(char *second_cmd)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (second_cmd[i] == '-')
		i++;
	while (second_cmd[i] != '\0')
	{
		if (ft_isalnum(second_cmd[i]) != 4)
			res = -1;
		i++;
	}
	return (res);
}

void	f_exit_args(int size, char *second_cmd, t_minish *sh)
{
	unsigned char	check_valid_arg;
	int				length_check;
	int				res;

	if (size > 2)
		exit_err_msg(NULL, -1, sh);
	res = check_number_or_not(second_cmd);
	if (res == -1)
	{
		exit_err_msg(second_cmd, -2, sh);
		return ;
	}
	length_check = check_input_length(second_cmd);
	if (length_check == -1)
	{
		exit_err_msg(second_cmd, 255, sh);
		return ;
	}
	check_valid_arg = ft_atol(second_cmd);
	f_exit_only(check_valid_arg, sh);
}

void	f_exit_only(int exitcode, t_minish *sh)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_all_envps(sh);
	free_minish(sh);
	exit(exitcode);
}

int	f_exit(t_minish *sh, t_ready *rdy)
{
	char	**cmds;
	int		size;

	cmds = rdy->cmd;
	size = f_count_char(cmds);
	if (size == 1)
	{
		*f_exitcode() = 0;
		f_exit_only(*f_exitcode(), sh);
	}
	else if (size > 1)
		f_exit_args(size, cmds[1], sh);
	return (0);
}
