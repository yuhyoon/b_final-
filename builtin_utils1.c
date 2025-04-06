/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/06 14:41:50 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*check_name_contains_equal_sign(char *cmd)
{
	int		i;
	int		total;
	char	*new_cmd;

	i = 0;
	total = ft_strlen(cmd);
	while (i < total)
	{
		if (cmd[i] == '=')
			return (NULL);
		i++;
	}
	new_cmd = ft_strjoin(cmd, "=");
	return (new_cmd);
}

static void	allocate_new_envp(char **new_envp, char *cmd, int envp_count)
{
	char	*new_cmd;

	new_envp[envp_count] = ft_strdup(cmd);
	new_cmd = check_name_contains_equal_sign(cmd);
	if (new_cmd != NULL)
	{
		free(new_envp[envp_count]);
		new_envp[envp_count] = ft_strdup(new_cmd);
		free(new_cmd);
	}
}

void	update_envp_array(t_minish *sh, char *cmd)
{
	int		new_count;
	int		i;
	char	**new_envp;

	new_count = sh->envp_count + 1;
	new_envp = (char **)malloc(sizeof(char *) * (new_count + 1));
	i = -1;
	while (++i < (sh->envp_count))
	{
		new_envp[i] = ft_strdup(sh->envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			exit(EXIT_FAILURE);
		}
	}
	allocate_new_envp(new_envp, cmd, sh->envp_count);
	new_envp[sh->envp_count + 1] = NULL;
	free_double_char(sh->envp);
	sh->envp = new_envp;
}
