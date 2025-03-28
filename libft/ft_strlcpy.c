/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:52:53 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/04 20:59:28 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*s;
	size_t	src_len;
	size_t	i;

	s = (char *)src;
	i = 0;
	src_len = ft_strlen(s);
	if (dstsize == 0)
		return (src_len);
	while (s[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
