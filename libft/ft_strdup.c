/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:17:24 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/29 10:44:17 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char			*dst;
	unsigned int	src_len;

	src_len = ft_strlen(src);
	dst = (char *)malloc(sizeof(char) * (src_len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, (src_len + 1));
	return (dst);
}
