/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:42:56 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/03 10:44:09 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_ex_src(char *msk_spn, char *src_spn, t_minish *sh);

int	count_text(char *mask)
{
	int	i;

	i = 0;
	while (mask[i] != PIPE && mask[i] != '\n' && mask[i] != NONE)
	{
		i++;
	}
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

char	*mask_to_str(int len, char *mask)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	ft_memset(str, 0, len + 1);
	str = ft_memcpy(str, mask, len);
	return (str);
}

char	*get_submask(t_ready *rdy, char *subsrc, char *mask)
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

t_compare	*create_compare(t_ready *rdy, int cur_idx, int end)
{
	char	*src_span;
	char	*msk_span;
	t_compare	*cmpare;

	src_span = ft_substr(rdy->subsrc, cur_idx, end);
	msk_span = ft_substr(rdy->submsk, cur_idx, end);
	cmpare = malloc(sizeof(t_compare));
	cmpare->src_span = src_span;
	cmpare->msk_span = msk_span;
	return (cmpare);
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
		ft_lstadd_back(&lst, ft_lstnew(compare));
		cur_idx += end;
	}
	return (lst);
}


int	ft_ismetas(char *msk)
{
	int	len;
	int	i;
	int	flg;
	int	metas;

	len = ft_strlen(msk);
	i = 0;
	flg = 0;
	metas = 1;
	while(i < len)
	{
		if ((msk[i] - 48) == DOLLAR || (msk[i] - 48) == PIPE)
		{
			flg = flg + (metas * (msk[i] - 48));
			metas *= 10;
		}
		i++;
	}
	return (flg);
}



void	expension(t_list *lst, t_minish *sh)
{
	char	*msk_spn;
	char	*src_spn;
	int		i;
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

char	*create_str_1(t_list **head);
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

int		count_contents_size(t_list *head)
{
	int		size;
	t_list	*lst;
	
	lst = head;
	size = 0;
	while(lst)
	{
		size += ft_strlen((char *)lst->content);
		lst = lst->next;
	}
	return (size);
}

char	*create_str_1(t_list **head)
{
	char	*str;
	char	*cur;
	char	*next;
	t_list	*lst;

	lst = *head;
	str = NULL;
	while(lst->next != NULL)
	{
		cur = lst->content;
		if (str != NULL)
			cur = str;
		next = lst->next->content;
		str = ft_strjoin(cur, next);
		lst = lst->next;
	}
	if (ft_lstsize(*head) == 1)
		str = ft_strdup((char *)lst->content);
	return (str);
}

void	create_text_list(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
	int		i;

	i = 0;
	while (mask[i] != '\n' && mask[i] != PIPE)
		i++;
	rdy->subsrc = ft_substr(src, 0, i);
	rdy->submsk = get_submask(rdy, rdy->subsrc, mask);
	rdy->text = get_compare_list(rdy, i);
	expension(rdy->text, sh);
	//rdy->text = head;
}
