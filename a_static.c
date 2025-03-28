/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_static.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:57:53 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/28 17:58:28 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	*f_exitcode(void)
{
	static int	i;

	return (&i);
}

static	t_struct	**get_allocation_list(void)
{
	static t_struct	*allocations;

	allocations = NULL;
	return (&allocations);
}

void	*ft_malloc(size_t size)
{
	void		*ptr;
	t_struct	*new_node;
	t_struct	**allocations;

	ptr = malloc(size);
	if (!ptr)
		*f_exitcode() = 1;
	new_node = malloc(sizeof(t_struct));
	if (!new_node)
	{
		free(ptr);
		*f_exitcode() = 1;
	}
	new_node->ptr = ptr;
	allocations = get_allocation_list();
	new_node->next = *allocations;
	*allocations = new_node;
	return (ptr);
}

void	ft_free_all(void)
{
	t_struct	**allocations;
	t_struct	*cur;
	t_struct	*next;

	allocations = get_allocation_list();
	cur = *allocations;
	while (cur)
	{
		next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
	*allocations = NULL;
}
