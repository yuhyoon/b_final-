/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:27:36 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/06 14:42:28 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	size_t			i;
	unsigned char	cc;

	s = (unsigned char *)str;
	i = 0;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (*s == cc)
			return (s);
		s++;
		i++;
	}
	return (0);
}
