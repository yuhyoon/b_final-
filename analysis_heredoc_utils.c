/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.gyeongsan>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:08:55 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/23 17:08:55 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"

void    restore_terminal(void)
{
    int     tty_fd;
    char    *tty_path;
    
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
