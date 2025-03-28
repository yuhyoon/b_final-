/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/26 15:37:20 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//header는 합칠때 다시 만지기...
#include "builtin.h"
#include "a_static.h"

int	f_cd_root(void)
{
	if (chdir("/") == -1)
	{
		ft_putstr_fd("bash: cd: Failed to change to root directory\n", 2);
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
	if (access(location, F_OK) == -1)
	{
		f_putstr_fd_error_msg("cd", "Permission denied", location, 2);
		*f_exitcode() = 1;
		return (1);
	}
	if (location[0] != '\\')
		res = chdir(location);
	else
	{
		f_putstr_fd_error_msg("cd", "No such file or directory", location, 2);
		*f_exitcode() = 1;
		return (1);
	}
	*f_exitcode() = 0;
	return (res);
}

int	f_cd_home(t_minish *sh)
{
	char	*home;

	home = f_getenv(sh->envp, "HOME");
	if (!home)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		*f_exitcode() = 1;
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("bash: cd: Failed to change directory to HOME\n", 2);
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
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		*f_exitcode() = 1;
		return (1);
	}
	if (chdir(back) == -1)
	{
		ft_putstr_fd("bash: cd: Failed to change directory to OLDPWD\n", 2);
		*f_exitcode() = 1;
		return (1);
	}
	ft_putstr_fd(back, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	*f_exitcode() = 0;
	return (0);
}

