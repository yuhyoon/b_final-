/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:49:16 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/26 15:33:27 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int is_valid_name(char *name);

void	update_or_add_envps(t_minish *sh, char *cmd)
{
	int i = 0;
	update_envp_array(sh, cmd);
	sh->envp_count++;
	update_or_add_envp_node(&(sh->n_export), cmd);
	update_or_add_envp_node(&(sh->n_envs), cmd);
}

// export 정렬
void	bubble_sort_envp(char **envp, int count)
{
	int i;
	int j;
	char *temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// export node 생성
void	f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
{
	int		count;
	int		i;
	char	**sorted_envp_array;

	count = f_count_char(envp);
	i = -1;
	sorted_envp_array = NULL;
	if (!envp || !sorted_envp)
	{
		ft_putstr_fd("Invalid Inputs", STDERR_FILENO); // 지우기
		return;
	}
	sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!sorted_envp_array)
	{
		ft_putstr_fd("Failed allocated", STDERR_FILENO); // 지우기
		return;
	}
	while (++i < count)
		sorted_envp_array[i] = ft_strdup(envp[i]);
	sorted_envp_array[i] = NULL;
	bubble_sort_envp(sorted_envp_array, count);
	f_init_env(sorted_envp_array, sorted_envp);
	free_double_char(sorted_envp_array);
}

void print_export(t_envp *lst)
{
	while (lst)
	{
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(lst->key, 2);
		if (lst->value)
		{
			ft_putstr_fd("=\"", 2);
			ft_putstr_fd(lst->value, 2);
			ft_putstr_fd("\"", 2);
		}
		ft_putstr_fd("\n", 2);
		lst = lst->next;
	}
}

void export_err_msg(char *cmds)
{
	int i;
	int size;

	i = -1;
	size = ft_strlen(cmds);
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	if (*cmds && cmds) // if (cmds && !(cmds[0] == '\0' && cmds[0] == ' '))
	{
		while (++i < size)
			write(STDERR_FILENO, &cmds[i], 1);
	}
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
}

char	*get_name_in_value(char *value, int *i)
{
	char	*find_var;
	int		start;
	int		end;
	int		length;
	int		j;
	
	start = *i + 1;
	end = start;
	while (value[end] && value[end] != ' ' && value[end] != '\"')
		end++;
	length = end - start;
	find_var = (char *)malloc(sizeof(char) * (length + 1));
	if (!find_var)
		return (NULL);
	j = 0;
    while (j < length) 
	{
        find_var[j] = value[start + j];
        j++;
    }
	find_var[length] = '\0';
	return (find_var);
}

int is_valid_name(char *name)
{
	int valid;
	int flag;
	int i;

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
	if (flag == 1 && name[(i + 1)] != '\0') //key (0) / = (0) / value (0)
		return (2);
	if (flag == 0 && name[i] == '\0')
		return (0); // key (0) / = (x) / value (x)
	return (1);
}

// int	is_valid_value2(char **cmd, size_t *index_stack, char *original_cmd, int is_name, t_minish *sh)
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
// 	if (is_name == 2 || is_name == 0)
// 		update_or_add_envps(sh, *cmd);
// 	else if (is_name == 1)
// 	{
// 		if (original_cmd[tmp_i] == ' ')
// 			update_or_add_envps(sh, *cmd);
// 		else
// 		{
// 			if (*(cmd + 1) == NULL)
// 				update_or_add_envps(sh, *cmd);
// 			else
// 			{
// 				new_cmd = ft_strjoin(*cmd, *(cmd + 1));
// 				update_or_add_envps(sh, new_cmd);
// 				free(new_cmd);
// 				return (2);
// 			}
// 		}
// 	}
// 	else if (is_name == -1)
// 		return (-1);
// 	return (0);
// }

int is_valid_value2(char **cmd, size_t *index_stack, char *original_cmd, int is_name, t_minish *sh)
{
    int     length_original_cmds;
    char    *find_in_o_cmd;
    int     index;
	int		res;

    length_original_cmds = ft_strlen(original_cmd);
    find_in_o_cmd = ft_strnstr(&(original_cmd[*index_stack]), *cmd, length_original_cmds);
    index = (find_in_o_cmd - original_cmd);
    (*index_stack) = index + 1;

	res = process_envp_update(cmd, index, original_cmd, is_name, sh);
    return (res); 
}


int process_envp_update(char **cmd, int index, char *original_cmd, int is_name, t_minish *sh)
{
    int     tmp_i;
    char    *new_cmd;

    tmp_i = index + 2;
    if (is_name == 2 || is_name == 0)
        update_or_add_envps(sh, *cmd);
    else if (is_name == 1)
    {
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
    }
    else if (is_name == -1)
        return (-1);
    return (0);
}


void	export_update_or_add(char **cmds, char *original_cmd, t_minish *sh)
{
	int		is_name;
	int		is_value;
	size_t	index_stack;
	char	**current_cmd = cmds;

	index_stack = ft_strlen(*current_cmd);
	current_cmd++;
	while (*current_cmd != NULL)
	{
		is_name = is_valid_name(*current_cmd);
		is_value = is_valid_value2(current_cmd, &index_stack, original_cmd, is_name, sh);
		if (is_value == 2)
			current_cmd++;
		else if (is_value == -1)
			export_err_msg(*current_cmd);
		current_cmd++;
	}
}

int f_export(t_minish *sh)
{
	int		size;
	char	**cmds;
	char	*original_cmd;

	original_cmd = sh->src;
	cmds = ((t_ready *)sh->ready->content)->cmd;
	size = f_count_char(cmds);
	if (size == 1)
		print_export(sh->n_export);
	else if (size > 1)
		export_update_or_add(cmds, original_cmd, sh);
	*f_exitcode() = 0;
	return (0); // 정상 종료
}