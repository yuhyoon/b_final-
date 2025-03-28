/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.gyeongsan>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:58:44 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/23 16:58:44 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child_process.h"
#include "a_static.h"

int	execute_bulitin(t_child_process *child, t_minish *sh, t_ready *rdy)
{
	int	res;

	res = 0;
	if (child->bulitin_code == 1)
		res = f_cd(sh);
	else if (child->bulitin_code == 2)
		res = f_echo(sh,rdy);
	else if (child->bulitin_code == 3)
		res = f_pwd(rdy);			
	else if (child->bulitin_code == 4)
		res = f_export(sh);
	else if (child->bulitin_code == 5)
		res = f_env(sh);
	else if (child->bulitin_code == 6)
		res = f_unset(sh);
	else if (child->bulitin_code == 7)
		res = f_exit(sh, rdy);
	child->state = STATE_COMPLETE;
	return (res);
}

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (-1);
	if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name) + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name) + 1) == 0)
		return (2);
	else if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name) + 1) == 0)
		return (3);
	else if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name) + 1) == 0)
		return (4);
	else if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name) + 1) == 0)
		return (5);
	else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name) + 1) == 0)
		return (6);
	else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name) + 1) == 0)
		return (7);
	return (0);
}
