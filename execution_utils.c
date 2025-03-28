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
	int		size;
	char	**str;
	t_list	*tmp;
	int		i;

	size = ft_lstsize(*head);
	str = malloc(sizeof(char *) * (size + 1));
	i = 0;
	tmp = *head;
	while (i < size)
	{
		str[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	str[i] = '\0';
	return (str);
}
