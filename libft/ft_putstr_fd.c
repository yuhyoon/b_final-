/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:13:26 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/22 15:16:29 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	i = 0;
	while (i < s_len)
	{
		write(fd, s + i, 1);
		i++;
	}
}
