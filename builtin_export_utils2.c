/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:49:16 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/28 13:18:11 by yuhyoon          ###   ########.fr       */
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
			break;
		}
		i++;
	}
	if (flag == 1 && name[i + 1] != '\0')
		return (2);
	if (flag == 0 && name[i] == '\0')
		return (0);
	return (1);
}

size_t	find_cmd_in_original(char *original_cmd, char *cmd, size_t index_stack)
{
	char	*find_in_o_cmd;
	int		res;

	find_in_o_cmd = ft_strnstr(&(original_cmd[index_stack]), cmd, ft_strlen(original_cmd));
	res = (find_in_o_cmd - original_cmd) + 1;
	return (res);
}

int	handle_name_case(char **cmd, char *original_cmd, int tmp_i, t_minish *sh)
{
	char	*new_cmd;

	if (original_cmd[tmp_i] == ' ')
		update_or_add_envps(sh, *cmd);
	else
	{
		if (*(cmd + 1) == NULL)
			update_or_add_envps(sh, *cmd);
		else
		{
			new_cmd = ft_strjoin(*cmd, *(cmd + 1));
			update_or_add_envps(sh, new_cmd);
			free(new_cmd);
			return (2);
		}
	}
	return (0);
}

int	process_envp_update(char **cmd, char *original_cmd, int is_name, t_minish *sh)
{
	int tmp_i;
	int case_is_name_1;

	case_is_name_1 = 0;
	tmp_i = ft_strlen(*cmd) + 1;
	if (is_name == 2 || is_name == 0)
		update_or_add_envps(sh, *cmd);
	else if (is_name == 1)
		case_is_name_1 = handle_name_case(cmd, original_cmd, tmp_i, sh);
	else if (is_name == -1)
		return (-1);
	return (0);
}

void	export_update_or_add(char **cmds, char *original_cmd, t_minish *sh)
{
	size_t	index_stack;
	int		is_name;
	int		is_value;
	char	**current_cmd;

	index_stack = 0;
	is_name = 0;
	is_value = 0;
	current_cmd = cmds + 1;
	while (*current_cmd != NULL)
	{
		is_name = is_valid_name(*current_cmd);
		index_stack = find_cmd_in_original(original_cmd, *current_cmd, index_stack);
		is_value = process_envp_update(current_cmd, original_cmd, is_name, sh);
		if (is_value == 2)
			current_cmd++;
		else if (is_value == -1)
			export_err_msg(*current_cmd);
		current_cmd++;
	}
}

// int	is_valid_name(char *name)
// {
// 	int valid;
// 	int flag;
// 	int i;

// 	i = 0;
// 	flag = 0;
// 	valid = ft_isalnum(name[0]);
// 	if (!(valid == 1 || valid == 2 || name[0] == '_'))
// 		return (-1);
// 	while (name[i])
// 	{
// 		if (name[i] == '=')
// 		{
// 			flag = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (flag == 1 && name[(i + 1)] != '\0')
// 		return (2);
// 	if (flag == 0 && name[i] == '\0')
// 		return (0);
// 	return (1);
// }

// int	is_valid_value2(char **cmd, size_t *index_stack, char *original_cmd, int is_name, t_minish *sh)
// {
// 	int     length_original_cmds;
// 	char    *find_in_o_cmd;
// 	int     index;
// 	int		res;

// 	length_original_cmds = ft_strlen(original_cmd);
// 	find_in_o_cmd = ft_strnstr(&(original_cmd[*index_stack]), *cmd, length_original_cmds);
// 	index = (find_in_o_cmd - original_cmd);
// 	(*index_stack) = index + 1;

// 	res = process_envp_update(cmd, index, original_cmd, is_name, sh);
// 	return (res); 
// }

// int	process_envp_update(char **cmd, int index, char *original_cmd, int is_name, t_minish *sh)
// {
// 	int		tmp_i;
// 	char	*new_cmd;
// 	int		res;

// 	res = 0;
// 	tmp_i = index + 2;
// 	if (is_name == 2 || is_name == 0)
// 		update_or_add_envps(sh, *cmd);
// 	else if (is_name == 1)
// 	{
// 		// if (original_cmd[tmp_i] == ' ')
// 		// 	update_or_add_envps(sh, *cmd);
// 		// else
// 		// {
// 		// 	if (*(cmd + 1) == NULL)
// 		// 		update_or_add_envps(sh, *cmd);
// 		// 	else
// 		// 	{
// 		// 		new_cmd = ft_strjoin(*cmd, *(cmd + 1));
// 		// 		update_or_add_envps(sh, new_cmd);
// 		// 		free(new_cmd);
// 		// 		return (2);
// 		// 	}
// 		// }
// 	}
// 	else if (is_name == -1)
// 		return (-1);
// 	return (0);
// }


// void	export_update_or_add(char **cmds, char *original_cmd, t_minish *sh)
// {
// 	int		is_name;
// 	int		is_value;
// 	size_t	index_stack;
// 	char	**current_cmd = cmds;

// 	index_stack = ft_strlen(*current_cmd);
// 	current_cmd++;
// 	while (*current_cmd != NULL)
// 	{
// 		is_name = is_valid_name(*current_cmd);
// 		is_value = is_valid_value2(current_cmd, &index_stack, original_cmd, is_name, sh);
// 		if (is_value == 2)
// 			current_cmd++;
// 		else if (is_value == -1)
// 			export_err_msg(*current_cmd);
// 		current_cmd++;
// 	}
// }

// int	f_export(t_minish *sh)
// {
// 	int		size;
// 	char	**cmds;
// 	char	*original_cmd;

// 	original_cmd = sh->src;
// 	cmds = ((t_ready *)sh->ready->content)->cmd;
// 	size = f_count_char(cmds);
// 	if (size == 1)
// 		print_export(sh->n_export);
// 	else if (size > 1)
// 		export_update_or_add(cmds, original_cmd, sh);
// 	*f_exitcode() = 0;
// 	return (0);
// }
