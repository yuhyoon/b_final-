/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:10:39 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/07 13:11:37 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	after_unset_new_envp(t_envp **head, t_minish *sh)
{
	t_envp	*current;
	char	*new_name;
	int		i;

	if (!head || !*head)
		return ;
	current = *head;
	free_double_char(sh->envp);
	sh->envp = (char **)malloc(sizeof(char *) * (sh->envp_count + 1));
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

int	f_unset(t_minish *sh, t_ready *rdy)
{
	char	**cmds;
	int		size;
	int		i;

	cmds = rdy->cmd;
	size = f_count_char(cmds);
	if (size > 1)
	{
		i = 1;
		while (i < size)
		{
			delete_t_envp(&(sh->n_export), cmds[i]);
			delete_t_envp(&(sh->n_envs), cmds[i]);
			after_unset_new_envp(&(sh->n_export), sh);
			i++;
		}
	}
	return (0);
}
