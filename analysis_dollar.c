/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:42:56 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/11 02:45:43 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	expension(t_list *lst, t_minish *sh)
{
	char	*msk_spn;
	char	*src_spn;
	char	*tmp;

	while (lst)
	{
		msk_spn = ((t_compare *)lst->content)->msk_span;
		if (ft_ismetas(msk_spn) > 0)
		{
			src_spn = ((t_compare *)lst->content)->src_span;
			tmp = get_ex_src(msk_spn, src_spn, sh);
			free(src_spn);
			((t_compare *)lst->content)->src_span = tmp;
		}
		lst = lst->next;
	}
}

char	*get_ex_src(char *msk_spn, char *src_spn, t_minish *sh)
{
	int		i;
	t_list	*head;
	char	*ex_src;
	int		len;

	i = 0;
	head = NULL;
	len = ft_strlen(msk_spn);
	while (i < len)
	{
		if ((msk_spn[i] - 48) == TEXT)
			i += get_plain_text(&msk_spn[i], "1", &src_spn[i], &head);
		else if ((msk_spn[i] - 48) == DOLLAR)
			i += get_variable(&msk_spn[i], &src_spn[i], &head, sh);
		else
			i++;
	}
	ex_src = create_str_1(&head);
	ft_lstclear(&head, del_text);
	return (ex_src);
}

int	get_plain_text(char *s1, char *s2, char *src, t_list **head)
{
	int		i;
	char	*rsult;
	t_list	*new;

	i = 0;
	while ((s1[i] - 48) == (*s2 - 48))
		i++;
	rsult = malloc(sizeof(char) * (i + 1));
	ft_memcpy(rsult, src, i);
	rsult[i] = '\0';
	new = ft_lstnew(rsult);
	ft_lstadd_back(head, new);
	return (i);
}

int	get_variable(char *mask, char *src, t_list **head, t_minish *sh)
{
	int		i;
	char	*rsult;
	t_list	*new;

	i = 1;
	if (mask[i] - 48 == 0 || mask[i] - 48 == '\n')
		rsult = ft_substr(src, 0, 1);
	else if (src[i++] == '?')
		rsult = ft_itoa(*f_exitcode());
	else
	{
		while (mask[i] - 48 == 1)
			i++;
		rsult = valid_env(ft_substr(src, 1, i - 1), sh);
	}
	new = ft_lstnew(rsult);
	ft_lstadd_back(head, new);
	return (i);
}

char	*valid_env(char *tmp, t_minish *sh)
{
	char	*env;

	env = f_getenv(sh->envp, tmp);
	if (env == NULL)
	{
		env = malloc(sizeof(char));
		*env = '\0';
	}
	else
	{
		env = ft_strdup(env);
		free(tmp);
	}
	return (env);
}
