/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/09 01:10:40 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
		if (ft_strncmp(current->key, key, (ft_strlen(current->key) + 1)) == 0)
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
		if (ft_strncmp(node->key, key, ft_strlen(node->key) + 1) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			return (1);
		}
		node = node->next;
	}
	return (0);
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

int	update_envp_node(t_envp **head, char *key, char *value)
{
	t_envp	*current;

	current = *head;
	while (current)
	{
		if ((ft_strlen(key) == ft_strlen(current->key)) && \
		ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			if (value != NULL)
			{
				free(current->value);
				current->value = ft_strdup(value);
				if (!current->value)
					return (-1);
			}
			return (0);
		}
		current = current->next;
	}
	return (1);
}
