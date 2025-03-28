/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/28 12:22:22 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	new_envp[sh->envp_count] = ft_strdup(cmd);
	new_envp[sh->envp_count + 1] = NULL;
	free_double_char(sh->envp);
	sh->envp = new_envp;
}

void	f_init_env(char **envp, t_envp **n_envps)
{
	int		i;
	t_envp	*tmp;

	tmp = new_node(envp, 0);
	*n_envps = tmp;
	i = 0;
	while (envp[++i])
	{
		tmp->next = new_node(envp, i);
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

t_envp	*new_node(char **envp, int idx)
{
	t_envp	*first;
	char	**split_envp;
	int		count;

	count = f_count_char(envp);
	first = (t_envp *)malloc(sizeof(t_envp));
	if (!first)
		return (NULL);
	split_envp = ft_split(envp[idx], '=');
	first->key = ft_strdup(split_envp[0]);
	if (split_envp[1] == NULL || split_envp[1][0] == '\0')
		first->value = ft_strdup("\0");
	else
		first->value = ft_strdup(split_envp[1]);
	first->count = count;
	first->next = NULL;
	free_double_char(split_envp);
	return (first);
}

void	delete_t_envp(t_envp **head, char *key)
{
	t_envp	*current;
	t_envp	*prev;

	if (!head || !*head)
		return ;
	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	update_t_envp(t_envp *node, char *key, char *value)
{
	while (node != NULL)
	{
		if (strcmp(node->key, key) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			return (1);
		}
		node = node->next;
	}
	return (0);
}
