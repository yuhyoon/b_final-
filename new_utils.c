/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:40:21 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/12 23:43:47 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	pipex_get_size(char *s, int len)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < len)
	{
		if (s[i] != '\0')
		{
			cnt++;
			while (i < len && s[i] != '\0')
				i++;
		}
		if (i >= len)
			break ;
		i++;
	}
	return (cnt);
}

char	**pipex_splited(char *s_dup, int w, char **abs)
{
	int	cnt;
	int	index_jump;

	cnt = 0;
	while (cnt < w)
	{
		while (*s_dup == '\0')
			s_dup++;
		abs[cnt] = ft_strdup(s_dup);
		index_jump = ft_strlen(abs[cnt]);
		s_dup = s_dup + index_jump;
		cnt++;
	}
	abs[cnt] = NULL;
	return (abs);
}
