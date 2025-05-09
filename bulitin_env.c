/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:27:35 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_envp *list)
{
	while (list)
	{
		if (list->value)
		{
			if (ft_strlen(list->value) > 0)
			{
				write(STDOUT_FILENO, list->key, ft_strlen(list->key));
				write(STDOUT_FILENO, "=", 1);
				write(STDOUT_FILENO, list->value, ft_strlen(list->value));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		list = list->next;
	}
}

int	f_env(t_minish *sh, t_ready *rdy)
{
	int		size;
	char	**cmds;

	cmds = rdy->cmd;
	size = f_count_char(cmds);
	if (size == 1)
		print_env(sh->n_envs);
	*f_exitcode() = 0;
	return (0);
}
