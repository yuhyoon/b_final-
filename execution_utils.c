/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.gyeongsan>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:02:52 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/25 01:09:38 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_splited(char **abs)
{
	int	i;

	i = 0;
	if (!abs)
		return ;
	while (abs[i] != NULL)
	{
		free(abs[i]);
		abs[i] = NULL;
		i++;
	}
	free(abs);
}

char	**create_str_2(t_list **head)
{
	t_list	*tmp;
	char	*subsrc;
	char	**str;
	int		i;
	int		size;

	size = ft_lstsize(*head);
	str = malloc(sizeof(char *) * (size + 1));
	i = 0;
	tmp = *head;
	while (i < size)
	{
		subsrc = ((t_compare *)tmp->content)->src_span;
		str[i] = ft_strdup(subsrc);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}
