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

void    handle_heredoc_child(int write_fd, char *delimeter)
{
    char    *line;
    
    close_fd(write_fd - 1);
    set_signal_heredoc();
    while ((line = readline("> ")))
    {
        if (!line)
        {
            write(write_fd, "\n", 1);
            break;
        }
        else
        {
            if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
            {
                if (line)
                    free(line);
                break;
            }
            write(write_fd, line, ft_strlen(line));
            write(write_fd, "\n", 1);
            free(line);
        }
    }
    close_fd(write_fd);
    exit(0);
}

void    create_heredoc_pipe(int *read_fd, int *write_fd)
{
	int fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	*read_fd = fd[0];
	*write_fd = fd[1];
}

void    handle_heredoc_parent(t_redrct *rdrct, int read_fd, int write_fd)
{
    int status;

    close_fd(write_fd);
    if (wait(&status) == -1)
        exit(EXIT_FAILURE);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
    {
        // close_fd(read_fd);
        restore_terminal();
        rdrct->fd = read_fd;
        set_signal(before_readline);
        *f_exitcode() = 1;
        return;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
    {
        // close_fd(read_fd);
        rdrct->fd = read_fd;
        exit(EXIT_FAILURE);
    }
    set_signal(before_readline);
    rdrct->fd = read_fd;
}


void	f_heredoc(t_redrct *rdrct)
{
	pid_t	pid;
	int		read_fd;
	int		write_fd;

	set_signal_fork_heredoc();
	create_heredoc_pipe(&read_fd, &write_fd);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		handle_heredoc_child(write_fd, rdrct->obj);
	else
		handle_heredoc_parent(rdrct, read_fd, write_fd);
}