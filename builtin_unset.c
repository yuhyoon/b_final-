/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:10:39 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/28 12:22:19 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	delete_double_char(t_minish *sh, char *cmd)
{
	int		len_arr;
	int		i;
	char	*name;
	char	**new_envp;

	len_arr = f_count_char(sh->envp);
	i = -1;
	new_envp = (char **)malloc(sizeof(char *) * (len_arr));
	if (!new_envp)
		return ;
	name = ft_strjoin(cmd, "=");
	while (++i < len_arr)
	{
		if (ft_strncmp(sh->envp[i], name, ft_strlen(name)) <= 0)
			new_envp[i] = ft_strdup(sh->envp[i]);
	}
	new_envp[len_arr - 1] = NULL;
	free_double_char(sh->envp);
	sh->envp = new_envp;
	free(name);
}

int	f_unset(t_minish *sh)
{
	char	**cmds;
	int		size;
	int		i;

	cmds = ((t_ready *)sh->ready->content)->cmd;
	size = f_count_char(cmds);
	if (size > 1)
	{
		i = 1;
		while (i < size)
		{
			delete_t_envp(&(sh->n_export), cmds[i]);
			delete_t_envp(&(sh->n_envs), cmds[i]);
			delete_double_char(sh, cmds[i]);
			i++;
		}
	}
	sh->envp_count = sh->envp_count - (size - 1);
	return (0);
}
