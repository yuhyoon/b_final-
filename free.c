/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:22:57 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 09:55:52 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	dengling(void *content, int size_type)
{
	if (size_type == 1)
		free((char *)content);
	if (size_type == 4)
		free((pid_t *)content);
	content = NULL;
}

void	free_envp_list(t_envp **head)
{
	t_envp	*current;
	t_envp	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_init_envps(t_minish *sh)
{
	free_envp_list(&(sh->n_envs));
	free_envp_list(&(sh->n_export));
	free_double_char(sh->envp);
}

void	free_minish(t_minish *minish)
{
	if (minish->mask)
		free(minish->mask);
	if (minish->src)
		free(minish->src);
	if (minish->ready)
		ft_lstclear(&minish->ready, del_ready);
	if (minish->child_pids)
		free(minish->child_pids);
	minish->prev_for_pipe = -1;
	minish->mask = NULL;
	minish->src = NULL;
	minish->ready = NULL;
	minish->child_pids = NULL;
}
