/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:27:35 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/13 23:30:15 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int validate_env_value(char **cmd, size_t *index_stack, char *original_cmd, int is_name)
{
	int		length_original_cmds;
	char	*find_in_o_cmd;
	int		index;
	int		tmp_i;

	length_original_cmds = ft_strlen(original_cmd);
	find_in_o_cmd = ft_strnstr(&(original_cmd[*index_stack]), *cmd, length_original_cmds);
	index = (find_in_o_cmd - original_cmd);
	(*index_stack) = index + 1;
	tmp_i = index + 2;
	if (is_name == 2)
		return 3;
	else if (is_name == 1)
	{
		if (original_cmd[tmp_i] == ' ')
			return 1;
		else
		{
			if (*(cmd + 1) == NULL)
				return is_name;
			else
				return 2;
		}
	}
	return is_name;
}

int update_env_variable(char **cmd, int result, t_minish *sh)
{
	char	*new_cmd;

	if (result == 1 || result == 3)
	{
		update_or_add_envp_node(&(sh->n_envs), *cmd);
	}
	else if (result == 2)
	{
		new_cmd = ft_strjoin(*cmd, *(cmd + 1));
		update_or_add_envp_node(&(sh->n_envs), new_cmd);
		free(new_cmd);
	}
	else
	{
		if (*(cmd + 1) == NULL)
			update_or_add_envp_node(&(sh->n_envs), *cmd);
	}
	return (result);
}



// int	env_valid_value(char **cmd, size_t *index_stack, char *original_cmd, int is_name, t_minish *sh)
// {
// 	int		length_original_cmds;
// 	char	*find_in_o_cmd;
// 	char	*new_cmd;
// 	int		tmp_i;
// 	int		index;

// 	length_original_cmds = ft_strlen(original_cmd);
// 	find_in_o_cmd = ft_strnstr(&(original_cmd[*index_stack]), *cmd, length_original_cmds);
// 	index = (find_in_o_cmd - original_cmd);
// 	(*index_stack) = index + 1;
// 	tmp_i = index + 2;
// 	if (is_name == 2)
// 	{
// 		update_or_add_envp_node(&(sh->n_envs), *cmd);
// 		return (3);
// 	}
// 	else if (is_name == 1)
// 	{
// 		if (original_cmd[tmp_i] == ' ')
// 		{
// 			update_or_add_envp_node(&(sh->n_envs), *cmd);
// 			return (1);
// 		}
// 		else
// 		{
// 			if (*(cmd + 1) == NULL)
// 				update_or_add_envp_node(&(sh->n_envs), *cmd);
// 			else
// 			{
// 				new_cmd = ft_strjoin(*cmd, *(cmd + 1));
// 				update_or_add_envp_node(&(sh->n_envs), new_cmd);
// 				free(new_cmd);
// 				return (2);
// 			}
// 		}
// 	}
// 	return (is_name);
// }

void env_err_msg(char *cmds)
{
	int i;
	int size;

	i = -1;
	size = ft_strlen(cmds);
	ft_putstr_fd("minishell: env: ", STDERR_FILENO);
	ft_putstr_fd("\'", STDERR_FILENO);
	if (*cmds && cmds)
	{
		while (++i < size)
			write(STDERR_FILENO, &cmds[i], 1);
	}
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
}

void	print_env(t_envp *list)
{
	while (list)
	{
		if (ft_strncmp(list->key, "_", ft_strlen(list->key)) != 0)
		{
			write(STDOUT_FILENO, list->key ,ft_strlen(list->key));
			write(STDOUT_FILENO, "=", 1);
			if (list->value)
				write(STDOUT_FILENO, list->value, ft_strlen(list->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		list = list->next;
	}
}

void	env_delete(t_minish *sh, char **cmds)
{
	char	**current_cmd = cmds;

	while (*current_cmd != NULL)
	{
		delete_t_envp(&(sh->n_envs), *current_cmd);
		current_cmd++;
	}
}
int	env_valid_value(char **cmd, size_t *index_stack, char *original_cmd, int is_name, t_minish *sh)
{
	int result;

	result = validate_env_value(cmd, index_stack, original_cmd, is_name);
	result = update_env_variable(cmd, result, sh);
	return (result);
}

int valid_env_variables(char **cmds, char *original_cmd, t_minish *sh)
{
	int     is_name;
	int     is_value;
	size_t  index_stack;
	char    **current_cmd;
	
	current_cmd = cmds;
	index_stack = ft_strlen(*current_cmd);
	current_cmd++;
	while (*current_cmd != NULL)
	{
		is_name = is_valid_name(*current_cmd);
		is_value = env_valid_value(current_cmd, &index_stack, original_cmd, is_name, sh);
		if (is_value == 2)
			current_cmd++;
		else if (is_value == -1 || is_value == 0)
		{
			env_err_msg(*current_cmd);
			return (0);
		}
		current_cmd++;
	}
	return (1);
}

void env_update_or_add(char **cmds, char *original_cmd, t_minish *sh)
{
	int is_valid;

	is_valid = valid_env_variables(cmds, original_cmd, sh);
	if (is_valid)
	{
		print_env(sh->n_envs);
		env_delete(sh, cmds);
	}
}

int	vaild_check_value(char **cmd, size_t *index_stack, char *original_cmd, int is_name)
{
	int		length_original_cmds;
	char	*find_in_o_cmd;
	int		tmp_i;
	int		index;

	length_original_cmds = ft_strlen(original_cmd);
	find_in_o_cmd = ft_strnstr(&(original_cmd[*index_stack]), *cmd, length_original_cmds);
	index = (find_in_o_cmd - original_cmd);
	(*index_stack) = index + 1;
	tmp_i = index + 2;
	if (is_name == 2)
		return (3);
	else if (is_name == 1)
	{
		if (original_cmd[tmp_i] == ' ')
			return (1);
		else
		{
			if (*(cmd + 1) == NULL)
				return (is_name);
			else
				return (2);
		}
	}
	return (is_name);
}

void	f_env_valid_check(char **cmds, char *original_cmd, t_minish *sh)
{
	int     is_name;
	int     is_value;
	size_t  index_stack;
	char    **current_cmd;
	
	current_cmd = cmds;
	index_stack = ft_strlen(*current_cmd);
	current_cmd++;
	while (*current_cmd != NULL)
	{
		is_name = is_valid_name(*current_cmd);
		is_value = vaild_check_value(current_cmd, &index_stack, original_cmd, is_name);
		if (is_value == 2)
			current_cmd++;
		else if (is_value == -1 || is_value == 0)
		{
			env_err_msg(*current_cmd);
			return ;
		}
		current_cmd++;
	}
	env_update_or_add(cmds, original_cmd, sh);
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
	else if (size > 1)
		f_env_valid_check(cmds, original_cmd, sh);
		// env_update_or_add();
	*f_exitcode() = 0;
	return (0);
}
