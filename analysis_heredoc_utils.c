/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_heredoc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:08:55 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_terminal(void)
{
	int		tty_fd;
	char	*tty_path;

	tty_path = ttyname(0);
	if (tty_path)
	{
		tty_fd = open(tty_path, O_RDWR);
		if (tty_fd != -1)
		{
			dup2(tty_fd, 0);
			close(tty_fd);
		}
	}
}

void	close_fd(int fd)
{
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
}
