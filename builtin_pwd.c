/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:59:30 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/03 11:04:43 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	f_pwd(t_ready *rdy)
{
	(void)rdy;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		*f_exitcode() = 1;
		return (1);
	}
	ft_putstr_fd(new_pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(new_pwd);
	*f_exitcode() = 0;
	return (0);
}
