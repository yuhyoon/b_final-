/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:01:31 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/10 18:46:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_envp	*create_new_node(char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->count = 1;
	new_node->next = NULL;
	return (new_node);
}

int	find_insert_position(t_envp *head, char *key, \
t_envp **prev, t_envp **current)
{
	*prev = NULL;
	*current = head;
	while (*current && ft_strncmp((*current)->key, key, ft_strlen(key) + 1) < 0)
	{
		*prev = *current;
		*current = (*current)->next;
	}
	return (0);
}

int	insert_node(t_envp **head, t_envp *new_node, t_envp *prev, t_envp *current)
{
	if (!prev)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		prev->next = new_node;
		new_node->next = current;
	}
	return (0);
}

int	add_envp_node(t_envp **head, char *key, char *value)
{
	t_envp	*new_node;
	t_envp	*current;
	t_envp	*prev;

	prev = NULL;
	new_node = create_new_node(key, value);
	if (!new_node)
		return (-1);
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	find_insert_position(*head, key, &prev, &current);
	insert_node(head, new_node, prev, current);
	return (0);
}

void	update_or_add_envp_node(t_envp **head, char *set)
{
	char	*value;
	char	**sets;
	char	*dup_set;
	int		len;

	len = ft_strlen(set);
	dup_set = ft_strdup(set);
	sets = ft_split(dup_set, '=');
	free(dup_set);
	value = NULL;
	if (sets[1] == NULL)
	{
		if (set[(len - 1)] == '=')
			value = ft_strdup("\0");
	}
	else
	{
		value = ft_strdup(sets[1]);
		if (!value)
			return ;
	}
	if (update_envp_node(head, sets[0], value) == 1)
		add_envp_node(head, sets[0], value);
	free_double_char(sets);
}
