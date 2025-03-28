/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/13 23:10:37 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//노드 free (free_minish)
void	free_node_t_envp(t_envp **envp) //전이름 : free_n_envps
{
	t_envp *current;
	t_envp *next;

	current = *envp;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

//더블차 갯수
int	f_count_char(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

//더블차 free
void	free_double_char(char **double_char)
{
    int i;
    int length;

	i = -1;
	length = f_count_char(double_char);
	while (++i < length)
        free(double_char[i]);
    free(double_char); 
}
