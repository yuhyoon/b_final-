/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
