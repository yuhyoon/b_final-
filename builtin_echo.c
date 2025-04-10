/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:47:10 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/10 18:45:14 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	f_print_echo(char **param_list, int *option_off)
{
	while (*param_list)
	{
		write(STDOUT_FILENO, *param_list, ft_strlen(*param_list));
		param_list++;
		if (*param_list && **param_list != '\0')
			write(STDOUT_FILENO, " ", 1);
	}
	if (!*option_off)
		write(STDOUT_FILENO, "\n", 1);
}

int	f_check_n_option(char *is_option)
{
	int	i;

	i = 1;
	if (is_option[0] != '-')
		return (0);
	while (is_option[0] == '-' && is_option[i] == 'n')
		i++;
	if (is_option[i] != '\0')
		return (0);
	return (1);
}

int	check_n_option(char **cmds, int size, int *flag)
{
	int		i;

	i = 1;
	while (i < size)
	{
		if (f_check_n_option(cmds[i]) == 1)
			*flag = 1;
		else
			break ;
		i++;
	}
	return (i);
}

void	process_echo(char **cmds, int size)
{
	int		start_idx;
	int		flag;

	flag = 0;
	start_idx = check_n_option(cmds, size, &flag);
	f_print_echo(&(cmds[start_idx]), &flag);
}

unsigned int	f_echo(t_ready *rdy)
{
	char	**cmds;
	int		size;

	cmds = rdy->cmd;
	size = f_count_char(cmds);
	*f_exitcode() = 0;
	if (size == 1)
		write(STDOUT_FILENO, "\n", 1);
	else if (size > 1)
		process_echo(cmds, size);
	if (*f_exitcode() > 0)
		return (*f_exitcode());
	return (*f_exitcode());
}
