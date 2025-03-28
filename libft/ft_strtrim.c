/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:02:01 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/01/31 15:12:41 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	char	*s_1;
	char	*sett;
	int		i;
	int		j;

	if (!s1)
		return (0);
	if (!set || !*set)
		return (ft_strdup((char *)s1));
	s_1 = (char *)s1;
	sett = (char *)set;
	i = 0;
	j = ft_strlen(s_1);
	while (ft_strchr(sett, s_1[i]) && i < j)
		i++;
	while (j > i && ft_strrchr(sett, s_1[j - 1]))
		j--;
	tmp = malloc(sizeof(char) * (j - i) + 1);
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, s_1 + i, (j - i) + 1);
	return (tmp);
}
