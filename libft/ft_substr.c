/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:03:10 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/17 23:30:13 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*subs;
	char				*ss;
	unsigned int		i;

	i = 0;
	subs = (char *)malloc((sizeof(char) * (len + 1)));
	ss = (char *)s;
	if (!subs || !s)
		return (0);
	if (ft_strlen(ss) < start || len < 1)
		return (ft_strdup(""));
	while (i < len && ss[start] != '\0')
	{
		subs[i] = ss[start];
		start++;
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
