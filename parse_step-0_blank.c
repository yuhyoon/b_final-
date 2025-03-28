/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-0_blank.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.gyeongsan>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:18:27 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/23 17:18:28 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_utils.h"
#include "parse.h"

char	*check_blank(char *mask)
{
	int	len;
	int	i;

	len = ft_strlen_delim(mask, '\n');
	i = 0;
	while (i < len && mask[i] == 0)
	{
		i++;
	}
	if (i == len)
		return (NULL);
	return (mask);
}
