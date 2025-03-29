/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:17:24 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/29 10:50:34 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*new_src;
	int		src_l;
	int		i;

	src_l = ft_strlen(src);
	new_src = (char *)malloc(sizeof(char) * (src_l + 1));
	if (!new_src)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		new_src[i] = src[i];
		i++;
	}
	new_src[i] = '\0';
	return (new_src);
}
