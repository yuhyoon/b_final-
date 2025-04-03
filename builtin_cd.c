/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/03 11:07:19 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	f_cd_root(void)
{
	if (chdir("/") == -1)
	{
		ft_putstr_fd("bash: cd: Failed to change to root directory\n", \
			STDERR_FILENO);
		*f_exitcode() = 1;
		return (1);
	}
	*f_exitcode() = 0;
	return (0);
}

int	f_cd_goto(char *location)
{
	int	res;

	res = 0;
	if (access(location, F_OK) != -1)
	{
		if (location[0] != '\\')
		{
			res = chdir(location);
			if (res == -1)
				res = cd_err_msg(location, 1, 1);
		}
		else
			res = cd_err_msg(location, 1, 2);
	}
	else
		res = cd_err_msg(location, 1, 3);
	*f_exitcode() = 0;
	return (res);
}

int	f_cd_home(t_minish *sh)
{
	char	*home;

	home = f_getenv(sh->envp, "HOME");
	if (!home)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO);
		*f_exitcode() = 1;
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("bash: cd: Failed to change \
		directory to HOME\n", STDERR_FILENO);
		*f_exitcode() = 1;
		return (1);
	}
	*f_exitcode() = 0;
	return (0);
}

int	f_cd_go_back(t_minish *sh)
{
	char	*back;

	back = f_getenv(sh->envp, "OLDPWD");
	if (!back)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO);
		*f_exitcode() = 1;
		return (1);
	}
	if (chdir(back) == -1)
	{
		ft_putstr_fd("bash: cd: Failed to change directory to OLDPWD\n", \
			STDERR_FILENO);
		*f_exitcode() = 1;
		return (1);
	}
	ft_putstr_fd(back, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	*f_exitcode() = 0;
	return (0);
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
