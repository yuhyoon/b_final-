/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:30:38 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/12 22:09:53 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
	{	
		if (c >= 65 && c <= 90)
			return (1);
		else if (c >= 97 && c <= 122)
			return (2);
		else if (c >= 48 && c <= 57)
			return (4);
	}
	return (0);
}
