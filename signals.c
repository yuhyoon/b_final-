/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:55:43 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/23 17:26:18 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_signal_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	before_readline(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		*f_exitcode() = 130;
		// *f_exitcode() = 130;
	}
}


void	set_signal(void *handler)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	after_cat_grep_c(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// *f_exitcode()
	}
	if (signal == SIGQUIT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// *f_exitcode()
	}
}

void	set_signal_cat_grep(void *handler)
{
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

