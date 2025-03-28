/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/28 04:43:02 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	update_envps(t_minish *sh, char *newpwd, char *oldpwd)
{
	char	*npwd;
	char	*opwd;

	npwd = ft_strjoin("PWD=", newpwd);
	if (!npwd)
		return (-1);
	opwd = ft_strjoin("OLDPWD=", oldpwd);
	if (!opwd)
		return (-1);
	update_or_add_envps(sh, npwd);
	update_or_add_envps(sh, opwd);
	return (0);
}

int	f_update_pwds(t_minish *sh, char *current_pwd)
{
	char	*oldpwd;
	char	*newpwd;

	*f_exitcode() = 1;
	oldpwd = ft_strdup(current_pwd);
	if (!oldpwd)
		return (1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		free(oldpwd);
		return (1);
	}
	if (update_envps(sh, newpwd, oldpwd))
	{
		free(oldpwd);
		free(newpwd);
		return (1);
	}
	free(oldpwd);
	free(newpwd);
	*f_exitcode() = 0;
	return (0);
}

void	f_putstr_fd_error_msg(char *builtin, char *msg, char *location, int fd)
{
	ft_putstr_fd("bash: ", fd);
	ft_putstr_fd(builtin, fd);
	ft_putstr_fd(": ", fd);
	if (location != NULL)
	{
		ft_putstr_fd(location, fd);
		ft_putstr_fd(": ", fd);
	}
	if (msg != NULL)
		ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
}

int	f_check_params(char *param1, int length)
{
	if (ft_strncmp(param1, "-", length) == 0)
		return (1);
	else if (ft_strncmp(param1, "~", length) == 0)
		return (2);
	else if (ft_strncmp(param1, "/", length) == 0)
		return (3);
	else
		return (4);
}

int	f_cd_process_params(t_minish *sh, t_list *commands)
{
	int	size;
	int	res;

	size = ft_lstsize(commands);
	if (size == 1)
		return (f_cd_home(sh));
	else if (size == 2)
	{
		res = f_check_params((char *)commands->next->content, \
			((int)ft_strlen((char *)commands->next->content)));
		if (res == 1)
			return (f_cd_go_back(sh));
		else if (res == 2)
			return (f_cd_home(sh));
		else if (res == 3)
			return (f_cd_root());
		else if (res == 4)
			return (f_cd_goto((char *)commands->next->content));
	}
	else
	{
		f_putstr_fd_error_msg("cd", "too many arguments", NULL, STDERR_FILENO);
		return (1);
	}
	return (0);
}
