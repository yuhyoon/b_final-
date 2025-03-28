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

void	f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
{
	int		count;
	int		i;
	char	**sorted_envp_array;

	count = f_count_char(envp);
	i = -1;
	sorted_envp_array = NULL;
	if (!envp || !sorted_envp)
		return;
	sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!sorted_envp_array)
		return;
	while (++i < count)
		sorted_envp_array[i] = ft_strdup(envp[i]);
	sorted_envp_array[i] = NULL;
	bubble_sort_envp(sorted_envp_array, count);
	f_init_env(sorted_envp_array, sorted_envp);
	free_double_char(sorted_envp_array);
}

void export_err_msg(char *cmds)
{
	int i;
	int size;

	i = -1;
	size = ft_strlen(cmds);
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	if (*cmds && cmds)
	{
		while (++i < size)
			write(STDERR_FILENO, &cmds[i], 1);
	}
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
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


void	update_or_add_envps(t_minish *sh, char *cmd)
{
	int i = 0;

	update_envp_array(sh, cmd);
	sh->envp_count++;
	update_or_add_envp_node(&(sh->n_export), cmd);
	update_or_add_envp_node(&(sh->n_envs), cmd);
}