/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.gyeongsan>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:42:56 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/26 13:38:26 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

	env = f_env(sh->envp, tmp);
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
	while (s1[i] == (*s2 - '0'))
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
	if (mask[i] == 0 || mask[i] == '\n')
		rsult = ft_substr(src, 0, 1);
	else if (src[i++] == '?')
		rsult = ft_itoa(*f_exitcode());
	else
	{
		while (mask[i] == 1)
			i++;
		rsult = valid_env(ft_substr(src, 1, i - 1), sh);
	}
	new = ft_lstnew(rsult);
	ft_lstadd_back(head, new);
	return (i);
}

void	create_text_list(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
	int		i;
	t_list	*head;

	i = 0;
	head = NULL;
	while (mask[i] != '\n' && mask[i] != PIPE)
	{
		if (mask[i] == 1)
			i += get_plain_text(&mask[i], "1", &src[i], &head);
		else if (mask[i] == 4)
			i += get_variable(&mask[i], &src[i], &head, sh);
		else
			i++;
	}
	rdy->text = head;
}
