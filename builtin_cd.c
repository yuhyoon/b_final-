/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/05 13:20:34 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	cd_err_msg(char *location, int exitstatus, int situation)
{
	int	res;

	res = 0;
	if (situation == 1)
		f_putstr_fd_error_msg("cd", "No such file or directory", location, \
			STDERR_FILENO);
	else if (situation == 2)
		f_putstr_fd_error_msg("cd", "Permission denied", location, \
			STDERR_FILENO);
	else if (situation == 3)
		f_putstr_fd_error_msg("cd", "No such file or directory", location, \
			STDERR_FILENO);
	res = exitstatus;
	*f_exitcode() = exitstatus;
	return (res);
}

int	f_cd(t_minish *sh, t_ready *rdy)
{
	int		res;
	char	*current_pwd;
	char	**cmds;

	res = -1;
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (1);
	cmds = rdy->cmd;
	res = f_cd_process_params(sh, cmds);
	if (res == 0)
		f_update_pwds(sh, current_pwd);
	free(current_pwd);
	return (res);
}
