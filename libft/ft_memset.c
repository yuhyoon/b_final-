/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:44:50 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/05 15:30:47 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*fromv;

	fromv = s;
	i = 0;
	while (i < n)
	{
		fromv[i] = (unsigned char)c;
		i++;
	}
	return (fromv);
}
