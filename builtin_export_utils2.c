/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:49:16 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/06 14:50:32 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_valid_name(char *name)
{
	int	valid;
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	valid = ft_isalnum(name[0]);
	if (!(valid == 1 || valid == 2 || name[0] == '_'))
		return (-1);
	while (name[i])
	{
		if (name[i] == '=')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 1 && name[(i + 1)] != '\0')
		return (2);
	if (flag == 0 && name[i] == '\0')
		return (0);
	return (1);
}

int	process_envp_update(t_env_context *ctx, t_minish *sh)
{
	int		tmp_i;
	char	*new_cmd;

	tmp_i = ctx->index + 2;
	if (ctx->is_name == -1)
		return (-1);
	if (ctx->is_name == 2 || ctx->is_name == 0 || \
		ctx->original_cmd[tmp_i] == ' ' || *(ctx->cmd + 1) == NULL)
		update_or_add_envps(sh, *(ctx->cmd));
	else if (ctx->is_name == 1)
	{
		new_cmd = ft_strjoin(*(ctx->cmd), *(ctx->cmd + 1));
		update_or_add_envps(sh, new_cmd);
		free(new_cmd);
		return (2);
	}
	return (0);
}

int	is_valid_value(t_env_context *ctx, size_t *index_stack, t_minish *sh)
{
	char	*find_in_o_cmd;
	int		length_original_cmds;
	int		res;

	length_original_cmds = ft_strlen(ctx->original_cmd);
	find_in_o_cmd = ft_strnstr(&(ctx->original_cmd[*index_stack]), \
	*(ctx->cmd), length_original_cmds);
	ctx->index = (find_in_o_cmd - ctx->original_cmd);
	(*index_stack) = ctx->index + 1;
	res = process_envp_update(ctx, sh);
	return (res);
}

void	export_update_or_add(char **cmds, char *original_cmd, t_minish *sh)
{
	int				is_name;
	int				is_value;
	size_t			index_stack;
	char			**current_cmd;
	t_env_context	ctx;

	current_cmd = cmds;
	index_stack = ft_strlen(*current_cmd);
	current_cmd++;
	while (*current_cmd && **current_cmd != '\0')
	{
		is_name = is_valid_name(*current_cmd);
		ctx.cmd = current_cmd;
		ctx.original_cmd = original_cmd;
		ctx.is_name = is_name;
		is_value = is_valid_value(&ctx, &index_stack, sh);
		if (is_value == 2)
			current_cmd++;
		else if (is_value == -1)
			export_err_msg(*current_cmd);
		current_cmd++;
	}
}
