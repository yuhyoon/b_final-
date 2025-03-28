/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:38:55 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/27 15:55:25 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_l;
	size_t	src_l;
	char	*s;

	i = 0;
	s = (char *)src;
	src_l = ft_strlen(s);
	if (dstsize == 0)
		return (src_l);
	dst_l = ft_strlen(dst);
	if (dstsize <= dst_l)
		return (dstsize + src_l);
	while ((s[i] != '\0') && (i + dst_l + 1) < dstsize)
	{
		dst[i + dst_l] = s[i];
		i++;
	}
	dst[dst_l + i] = '\0';
	return (dst_l + src_l);
}
