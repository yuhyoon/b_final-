/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:44:04 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/16 13:26:20 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*l;	

	i = 0;
	j = 0;
	b = (char *)big;
	l = (char *)little;
	if (l[i] == '\0' || !len)
		return (b);
	while (b[i] != '\0')
	{
		j = 0;
		while ((l[j] == b[i + j]) && (i + j < len) && b[i + j] != '\0')
		{
			if (l[j + 1] == '\0')
				return (b + i);
			j++;
		}
		i++;
	}
	return (0);
}
