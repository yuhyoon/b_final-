/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:54:55 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/18 16:38:31 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*s;
	size_t			i;

	s = (char *)str;
	i = (ft_strlen(s));
	if (c == '\0')
		return (s + i);
	while (i > 0)
	{
		i--;
		if (s[i] == c)
			return (s + i);
	}
	return (0);
}
