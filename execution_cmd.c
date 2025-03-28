/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:59:00 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 09:01:10 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	execute_cmd(t_child_process *child, t_minish *sh)
{
	if (execve(child->exe_path, &child->cmd[0], sh->envp) != -1)
		child->state = STATE_COMPLETE;
}

void	*access_exepath(t_child_process *child, t_ready *rdy)
{
	int		ok;
	int		n;
	t_ready	*rsult;

	ok = F_OK;
	n = -1;
	rsult = NULL;
	while (child->exe_path != NULL && \
			access(child->exe_path, ok) == 0 && ++n < 2)
		ok = X_OK;
	if (n < 2)
	{
		if (ok == F_OK && (ft_strchr(rdy->cmd[0], '/') == NULL))
			err_exec(127, rdy->cmd[0]);
		else if (ok == F_OK)
			err_such(127, rdy->cmd[0]);
		else if (ok == X_OK)
			err_permission(126, rdy->cmd[0]);
		free(child->exe_path);
	}
	else
		rsult = rdy;
	return (rsult);
}

char	*find_exepath(char *name, t_minish *sh)
{
	char	**env_paths;
	int		i;
	char	*cmd_path;
	char	*exe_path;

	if (*name == '\0')
		return (NULL);
	env_paths = ft_split(f_getenv(sh->envp, "PATH"), ':');
	cmd_path = ft_strjoin("/", name);
	i = 0;
	while (env_paths[i] != NULL)
	{
		exe_path = ft_strjoin(env_paths[i], cmd_path);
		if (access(exe_path, X_OK) == 0)
			break ;
		free(exe_path);
		exe_path = NULL;
		i++;
	}
	free_splited(env_paths);
	free(cmd_path);
	cmd_path = NULL;
	return (exe_path);
}

char	*get_exepath(t_ready *rdy, t_minish *sh)
{
	char	*name;
	char	*exe_path;

	name = (rdy->cmd[0]);
	if (ft_strchr(name, '/') == NULL)
		exe_path = find_exepath(name, sh);
	else
		exe_path = ft_strdup(name);
	return (exe_path);
}
