/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:39:26 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/26 10:40:04 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s1, const char *s2)
{
	size_t	cnt;

	cnt = 0;
	while (*s1 != '\0')
	{
		if (ft_strchr(s2, *s1) == NULL)
			cnt++;
		else
			return (cnt);
		s1++;
	}
	return (cnt);
}
