/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:29:42 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/20 13:00:01 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ss;
	size_t			s_len;
	unsigned int	i;
	char			*new_s;

	ss = (char *)s;
	s_len = ft_strlen(ss);
	i = 0;
	new_s = (char *)malloc(sizeof(char) * s_len + 1);
	if (!new_s)
		return (0);
	while (i < s_len)
	{
		new_s[i] = f(i, ss[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
