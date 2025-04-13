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

#include "main.h"

static char	*heredoc_child_in_while(int write_fd, char *delimeter)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		write(write_fd, "\n", 1);
		return (NULL);
	}
	else
	{
		if (ft_strncmp(line, delimeter, (ft_strlen(delimeter) + 1)) == 0)
		{
			free(line);
			return (NULL);
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
	}
	return (line);
}

void	handle_heredoc_child(int read_fd, int write_fd, char *delimeter)
{
	char	*line;

	close(read_fd);
	set_signal_heredoc();
	line = NULL;
	while (1)
	{
		line = heredoc_child_in_while(write_fd, delimeter);
		if (!line)
			break ;
		free(line);
	}
	close(write_fd);
	exit(0);
}

void	create_heredoc_pipe(int *read_fd, int *write_fd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	*read_fd = fd[0];
	*write_fd = fd[1];
}

void	handle_heredoc_parent(t_redrct *rdrct, int read_fd, \
	int write_fd, int *sig_c)
{
	int	status;

	close(write_fd);
	if (waitpid(-1, &status, 0) == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		*sig_c = 1;
		rdrct->fd = read_fd;
		close(read_fd);
		restore_terminal();
		*f_exitcode() = 130;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		rdrct->fd = read_fd;
		close(read_fd);
		exit(EXIT_FAILURE);
	}
	rdrct->fd = read_fd;
	set_signal(before_readline);
}

void	f_heredoc(t_redrct *rdrct, int *sig_c)
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
		handle_heredoc_child(read_fd, write_fd, rdrct->obj);
	else
		handle_heredoc_parent(rdrct, read_fd, write_fd, sig_c);
}
