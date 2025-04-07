/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:10:39 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/07 15:14:21 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
			after_update_new_envp(&(sh->n_export), sh);
			i++;
		}
	}
	return (0);
}
