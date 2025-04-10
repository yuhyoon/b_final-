/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-2_handle_tokens.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:15:33 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/11 02:44:59 by hyeyeom          ###   ########.fr       */
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

int	linked_to_arr(t_minish *sh, t_ready *rdy, int save)
{
	char	*mask;
	int		save_bckup;

	save_bckup = save;
	mask = sh->mask;
	if (rdy->rdrct != NULL)
		rdy->rdrct_num = ft_lstsize(rdy->rdrct);
	while (mask[save] != '\n' && mask[save] != PIPE)
		save++;
	if ((save == save_bckup && mask[save] == '\n') || \
		(check_blank(&mask[save_bckup], &mask[save]) && mask[save] == '\n'))
	{
		if (save_bckup != 0)
			err_syntax(2);
		return (-1);
	}
	else if (check_blank(&mask[save_bckup], &mask[save]) == NULL)
	{
		create_range_list(rdy, &sh->src[save_bckup], &sh->mask[save_bckup], sh);
		rdy->cmd = create_str_2(&rdy->text);
	}
	return (save);
}

int	handle_pipe(t_minish *sh, t_ready *current_rdy, t_list **rdrct, int save)
{
	t_ready	*next_rdy;
	t_list	*next_lst;
	int		save_bckup;
	char	*mask;

	mask = sh->mask;
	if (*rdrct != NULL)
		current_rdy->rdrct_num = ft_lstsize(*rdrct);
	save_bckup = save;
	while (mask[save] != '\n' && mask[save] != PIPE)
		save++;
	if (((save == save_bckup && mask[save] == PIPE) || \
	(check_blank(&mask[save_bckup], &mask[save]) && mask[save] == PIPE)))
	{
		err_syntax(2);
		return (9999);
	}
	else if (check_blank(&mask[save_bckup], &mask[save]) == NULL)
	{
		create_range_list(current_rdy, &sh->src[save_bckup], \
		&sh->mask[save_bckup], sh);
	}
	//current_rdy->cmd = create_str_2(&current_rdy->text);
	next_rdy = create_rdy();
	next_rdy->num = current_rdy->num + 1;
	next_lst = ft_lstnew(next_rdy);
	ft_lstadd_back(&sh->ready, next_lst);
	return (1);
}

//함수 분리 요망 ! (TOO_MANY_LINES)
int	parsing(t_minish *sh, int len)
{
	int		i;
	t_ready	*rdy;
	int		save;
	t_list	*lst;
	int		sig_c;

	i = 0;
	save = i;
	lst = init_parsing_structure(&sh->ready);
	sig_c = 0;
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
	if (i == len)
		i = linked_to_arr(sh, rdy, save);
	return (i);
}
