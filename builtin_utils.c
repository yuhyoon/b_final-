/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_list(t_envp *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

int	f_count_char(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

void	free_node_t_envp(t_envp **envp)
{
	t_envp	*current;
	t_envp	*next;

	current = *envp;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

void	free_double_char(char **double_char)
{
	int	i;
	int	length;

	i = -1;
	length = f_count_char(double_char);
	while (++i < length)
		free(double_char[i]);
	free(double_char);
	double_char = NULL;
}
