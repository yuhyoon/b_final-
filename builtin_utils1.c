/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/09 01:10:26 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*f_getenv(char **custom_envp, char *name)
{
	size_t	name_len;
	int		i;

	i = 0;
	if (!name || !custom_envp || ft_strlen(name) == 0)
		return (NULL);
	name_len = ft_strlen(name);
	while (custom_envp[i])
	{
		if (ft_strncmp(custom_envp[i], name, name_len) == 0 && \
		custom_envp[i][name_len] == '=')
			return (&custom_envp[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

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
