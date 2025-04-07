/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/07 16:44:07 by hyeyeom          ###   ########.fr       */
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

void	after_update_new_envp(t_envp **head, t_minish *sh)
{
	t_envp	*current;
	char	*new_name;
	int		i;

	if (!head || !*head)
		return ;
	current = *head;
	free_double_char(sh->envp);
	sh->envp = (char **)malloc(sizeof(char *) * (count_env_list(current) + 1));
	if (!sh->envp)
		return ;
	i = 0;
	while (current)
	{
		new_name = ft_strjoin(current->key, "=");
		if (current->value != NULL)
			sh->envp[i] = ft_strjoin(new_name, current->value);
		else
			sh->envp[i] = ft_strdup(new_name);
		free(new_name);
		current = current->next;
		i++;
	}
	sh->envp[i] = NULL;
	sh->envp_count = f_count_char(sh->envp);
}
