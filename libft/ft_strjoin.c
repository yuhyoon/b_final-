/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:46:31 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/14 21:02:04 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*s_1;
	char	*s_2;
	char	*joined;

	i = 0;
	s_1 = (char *)s1;
	s_2 = (char *)s2;
	joined = (char *)malloc(ft_strlen(s_1) + ft_strlen(s_2) + 1);
	if (!joined)
		return (0);
	while (i < ft_strlen(s_1))
	{
		joined[i] = s_1[i];
		i++;
	}
	while (i < ft_strlen(s_1) + ft_strlen(s_2) || *s_2)
	{
		joined[i] = *s_2;
		i++;
		s_2++;
	}
	joined[i] = '\0';
	return (joined);
}
