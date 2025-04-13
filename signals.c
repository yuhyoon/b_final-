/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:55:43 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_readline(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		*f_exitcode() = 130;
	}
}

void	set_signal(void *handler)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	after_cat_grep(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		*f_exitcode() = 130;
	}
	else if (signal == SIGQUIT)
	{
		write(STDERR_FILENO, "\n", 1);
		*f_exitcode() = 131;
	}
}

void	before_cat_grep(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	if (signal == SIGQUIT)
		write(STDERR_FILENO, "\n", 1);
}

void	set_signal_cat_grep(void *handler)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
