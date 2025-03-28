/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-1_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:57:28 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 08:57:29 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "error.h"

char	*syntax_result2(t_minish *sh, int result, char *mask)
{
	if (result > 0)
	{
		free(mask);
		mask = NULL;
		sh->exitcode = result;
		err_syntax(result);
		return (NULL);
	}
	return (mask);
}
