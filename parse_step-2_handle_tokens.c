/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-2_handle_tokens.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:15:33 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 18:31:10 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*create_rdy(void)
{
	t_ready	*rdy;

	rdy = malloc(sizeof(t_ready));
	ft_memset(rdy, 0, sizeof(t_ready));
	rdy->num = 1;
	rdy->input = STDIN_FILENO;
	rdy->output = STDOUT_FILENO;
	return (rdy);
}

t_list	*init_parsing_structure(t_list **rdy_head)
{
	t_ready	*rdy;

	rdy = create_rdy();
	ft_lstadd_back(rdy_head, ft_lstnew(rdy));
	return (*rdy_head);
}

void	linked_to_arr(t_minish *sh, t_ready *rdy, int save)
{
	if (rdy->rdrct != NULL)
		rdy->rdrct_num = ft_lstsize(rdy->rdrct);
	create_text_list(rdy, &sh->src[save], &sh->mask[save], sh);
	rdy->cmd = create_str_2(&rdy->text);
}

int	handle_pipe(t_minish *sh, t_ready *current_rdy, t_list **rdrct, int save)
{
	t_ready	*next_rdy;
	t_list	*next_lst;

	if (*rdrct != NULL)
		current_rdy->rdrct_num = ft_lstsize(*rdrct);
	create_text_list(current_rdy, &sh->src[save], &sh->mask[save], sh);
	current_rdy->cmd = create_str_2(&current_rdy->text);
	next_rdy = create_rdy();
	next_rdy->num = current_rdy->num + 1;
	next_lst = ft_lstnew(next_rdy);
	ft_lstadd_back(&sh->ready, next_lst);
	return (1);
}

//함수 분리 요망 ! (TOO_MANY_LINES)
void	*parsing(t_minish *sh, int len)
{
	int		i;
	t_ready	*rdy;
	int		save;
	t_list	*lst;
	int		sig_c;

	i = 0;
	save = i;
	lst = init_parsing_structure(&sh->ready);
	while (i < len)
	{
		if (sig_c == 1)
			return (0);
		rdy = ((t_ready *)lst->content);
		if (sh->mask[i] == IN_RD || sh->mask[i] == OUT_RD)
			i += create_rdrct(&sh->src[i], &sh->mask[i], &rdy->rdrct, &sig_c);
		else if (sh->mask[i] == PIPE)
		{
			i += handle_pipe(sh, rdy, &rdy->rdrct, save);
			lst = lst->next;
			save = i;
		}
		else
			i++;
	}
	linked_to_arr(sh, rdy, save);
	return (sh->ready);
}
