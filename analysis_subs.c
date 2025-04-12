/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_subs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:36:56 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/12 23:40:05 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	create_range_list(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (mask[i] != '\n' && mask[i] != PIPE)
		i++;
	rdy->subsrc = ft_substr(src, 0, i);
	rdy->submsk = get_submask(rdy->subsrc, mask);
	tmp = get_compare_list(rdy, i);
	rdy->text = extract_text(tmp);
	expension(rdy->text, sh);
}

t_list	*extract_text(t_list *list)
{
	t_list		*new;
	t_list		*head;
	t_compare	*cmpr;
	t_list		*lst;

	lst = list;
	head = NULL;
	while (lst)
	{
		cmpr = lst->content;
		if (!ft_strchr(cmpr->msk_span, 2 + 48) && \
		!ft_strchr(cmpr->msk_span, 3 + 48))
		{
			new = ft_lstnew(sep_rdrct(cmpr));
			ft_lstadd_back(&head, new);
		}
		lst = lst->next;
	}
	if (head == NULL)
		return (list);
	else
		return (head);
}

char	*get_submask(char *subsrc, char *mask)
{
	char	*printable_msk;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(subsrc);
	printable_msk = mask_to_str(len, mask);
	while (i < len)
	{
		printable_msk[i] += 48;
		i++;
	}
	return (printable_msk);
}

t_list	*get_compare_list(t_ready *rdy, int len)
{
	int			start;
	int			end;
	int			cur_idx;
	t_compare	*compare;
	t_list		*lst;

	cur_idx = 0;
	lst = NULL;
	while (cur_idx < len)
	{
		start = strspn(&rdy->submsk[cur_idx], "0");
		cur_idx += start;
		end = strcspn(&rdy->submsk[cur_idx], "0");
		compare = create_compare(rdy, cur_idx, end);
		if (compare == NULL)
			break ;
		ft_lstadd_back(&lst, ft_lstnew(compare));
		cur_idx += end;
	}
	return (lst);
}

t_compare	*create_compare(t_ready *rdy, int cur_idx, int end)
{
	char		*src_span;
	char		*msk_span;
	t_compare	*cmpare;

	src_span = ft_substr(rdy->subsrc, cur_idx, end);
	msk_span = ft_substr(rdy->submsk, cur_idx, end);
	if (*src_span == '\0')
	{
		free(src_span);
		free(msk_span);
		return (NULL);
	}
	else
	{
		cmpare = malloc(sizeof(t_compare));
		cmpare->src_span = src_span;
		cmpare->msk_span = msk_span;
	}
	return (cmpare);
}
