/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:17:04 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/06 14:22:55 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*n;
	int		flag;
	int		num;

	n = (char *)nptr;
	flag = 1;
	num = 0;
	while (*n != '\0')
	{
		while ((*n >= '\t' && *n <= '\r') || *n == ' ')
			n++;
		if (*n == '-' || *n == '+')
		{
			if (*n == '-')
				flag = -1;
			n++;
		}
		while (*n >= '0' && *n <= '9')
		{
			num = (num * 10) + (*n - 48);
			n++;
		}
		return (num * flag);
	}
	return (num);
}
