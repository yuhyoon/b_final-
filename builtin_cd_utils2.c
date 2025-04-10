/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/09 01:13:58 by hyeyeom          ###   ########.fr       */
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