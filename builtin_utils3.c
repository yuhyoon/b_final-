/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/28 12:22:27 by yuhyoon          ###   ########.fr       */
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

void	update_or_add_envp_node(t_envp **head, char *set)
{
	char	*key;
	char	*value;
	char	**sets;
	int		len;

	len = ft_strlen(set);
	sets = ft_split(set, '=');
	key = ft_strdup(sets[0]);
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
	if (update_envp_node(head, key, value) == 1)
		add_envp_node(head, key, value);
	free(key);
	free(value);
	free_double_char(sets);
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
