/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:56:54 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_such(int exit, char *obj)
{
	*f_exitcode() = exit;
	write(2, "minish: ", 8);
	write(2, obj, ft_strlen(obj));
	write(2, ": ", 2);
	write(2, "No such file or directory\n", 26);
}

void	err_permission(int exit, char *obj)
{
	*f_exitcode() = exit;
	write(2, "minish: ", 8);
	write(2, obj, ft_strlen(obj));
	write(2, ": ", 2);
	write(2, "Permission denied\n", 18);
}

void	err_exec(int exit, char *cmd_name)
{
	*f_exitcode() = exit;
	write(2, "minish: ", 8);
	write(2, cmd_name, (unsigned int)ft_strlen(cmd_name));
	write(2, " command not found\n", 19);
}

void	err_syntax(int syntax_result)
{
	if (syntax_result == 0)
		return ;
	*f_exitcode() = syntax_result;
	write(2, "minish: ", 8);
	if (syntax_result == 1)
		write(2, "syntax error!\n", 14);
	else if (syntax_result == 2)
		write(2, "syntax error! minishell don't support.\n", 39);
}
