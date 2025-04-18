/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:18:53 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/05 13:24:27 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*crr;

	i = 0;
	crr = (char *)s;
	while (i < n)
	{
		*crr = 0;
		crr++;
		i++;
	}
}
