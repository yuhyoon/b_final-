/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:27:35 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/28 12:43:30 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_env(t_envp *list)
{
	while (list)
	{
		if (ft_strncmp(list->key, "_", ft_strlen(list->key)) != 0)
		{
			write(STDOUT_FILENO, list->key, ft_strlen(list->key));
			write(STDOUT_FILENO, "=", 1);
			if (list->value)
				write(STDOUT_FILENO, list->value, ft_strlen(list->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		list = list->next;
	}
}

int	f_env(t_minish *sh)
{
	int		size;
	char	**cmds;
	char	*original_cmd;

	original_cmd = sh->src;
	cmds = ((t_ready *)sh->ready->content)->cmd;
	size = f_count_char(cmds);
	if (size == 1)
		print_env(sh->n_envs);
	*f_exitcode() = 0;
	return (0);
}
