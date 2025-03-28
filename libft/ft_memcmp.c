/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:50:24 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/06 14:33:37 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t cnt)
{
	size_t			i;
	unsigned char	*bf1;
	unsigned char	*bf2;

	i = 0;
	bf1 = (unsigned char *)buf1;
	bf2 = (unsigned char *)buf2;
	if (cnt == 0)
		return (0);
	while (((bf1[i]) == (bf2[i])) && i < cnt)
	{
		if (i == cnt - 1)
			return (0);
		i++;
	}
	return ((bf1[i]) - (bf2[i]));
}
