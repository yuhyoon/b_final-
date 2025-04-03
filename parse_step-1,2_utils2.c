/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-1,2_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:57:28 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/03 03:33:55 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*syntax_result2(t_minish *sh, int result, char *mask)
{
	if (result > 0)
	{
		free(mask);
		mask = NULL;
		err_syntax(result);
		return (NULL);
	}
	return (mask);
}
