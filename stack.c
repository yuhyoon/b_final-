/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:19:12 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_stack(t_stack *stack, void *top, int size)
{
	stack->top = top;
	stack->size = size;
}

int	is_emthy(t_stack *stack)
{
	if (stack->top == NULL)
		return (true);
	else
		return (false);
}

void	push(t_stack *stack, void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = data;
	new->next = stack->top;
	stack->top = new;
	stack->size++;
}

int	pop(t_stack *stack)
{
	t_list	*tmp;

	tmp = stack->top;
	stack->top = tmp->next;
	free(tmp);
	stack->size--;
	return (0);
}

void	*pop2(t_stack *stack)
{
	t_list	*tmp;
	void	*content;

	if (is_emthy(stack))
		return (NULL);
	tmp = stack->top;
	content = tmp->content;
	stack->top = tmp->next;
	free(tmp);
	stack->size--;
	return (content);
}
