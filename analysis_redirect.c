/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:59:33 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redrct	*init_rdrct(void)
{
	t_redrct	*rdrct;

	rdrct = malloc(sizeof(t_redrct));
	ft_memset(rdrct, 0, sizeof(t_redrct));
	return (rdrct);
}

void	valid_heredoc(t_redrct *new, t_minish *sh)
{
	if (new->parts == 2 && new->type == IN_RD)
	{
		if (!(new->obj) || ft_strlen(new->obj) < 1)
			err_syntax(2);
		else
			f_heredoc(new, sh);
	}
}

int	count_text(char *mask)
{
	int	i;

	i = 0;
	while (mask[i] != PIPE && mask[i] != '\n' && \
		mask[i] != NONE && mask[i] != QUOTE)
		i++;
	return (i);
}

int	create_rdrct(char *src, char *mask, t_list **head, t_minish *sh)
{
	int			i;
	t_redrct	*new;
	char		*str;
	int			len;
	t_list		*lst;

	lst = ft_lstnew(init_rdrct());
	i = 0;
	new = ((t_redrct *)((lst)->content));
	new->type = mask[i];
	while (mask[i] == new->type)
		i++;
	new->parts = i;
	while (mask[i] == NONE || mask[i] == QUOTE)
		i++;
	len = count_text(&mask[i]);
	ft_memset(&mask[i], new->type, len);
	str = malloc(sizeof(char) * (len + 1));
	ft_memcpy(str, &src[i], len);
	str[len] = '\0';
	new->obj = str;
	valid_heredoc(new, sh);
	ft_lstadd_back(head, lst);
	return (i + len);
}
