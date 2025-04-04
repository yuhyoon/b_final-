/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:49:16 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/04 14:17:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	f_export(t_minish *sh, t_ready *rdy)
{
	int		size;
	char	**cmds;
	char	*original_cmd;

	original_cmd = sh->src;
	cmds = rdy->cmd;
	size = f_count_char(cmds);
	if (size == 1)
		print_export(sh->n_export);
	else if (size > 1)
		export_update_or_add(cmds, original_cmd, sh);
	*f_exitcode() = 0;
	return (0);
}
