/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:50:24 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/16 13:22:45 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (!dest && !src)
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	if (d > s)
	{
		while (n--)
		{
			d[n] = s[n];
		}
		return (d);
	}
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}
	return (d);
}
