/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:19:12 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	queue(t_stack *stack, void *data)
{
	t_list	*new_node;
	t_list	*tmp;

	new_node = malloc(sizeof(t_list));
	new_node->content = data;
	new_node->next = NULL;
	if (stack->top == NULL)
		stack->top = new_node;
	else
	{
		tmp = stack->top;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	stack->size++;
}

void	*dequeue(t_stack *stack)
{
	t_list	*temp;
	void	*data;

	if (stack->top == NULL)
		return (NULL);
	temp = stack->top;
	data = temp->content;
	stack->top = stack->top->next;
	free(temp);
	stack->size--;
	return (data);
}
