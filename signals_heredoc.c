/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:55:43 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/23 17:49:54 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    sig_handler_heredoc(int signo)
{
    if (signo == SIGINT)
    {
        close(0);
        write(STDOUT_FILENO, "\n", 1);
        exit(130);
    }
}

void    set_signal_heredoc(void)
{
    struct sigaction sa;
    
    sa.sa_handler = sig_handler_heredoc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        exit(EXIT_FAILURE);
}

void    set_signal_fork_heredoc(void)
{
    struct sigaction sa;
    
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        exit(EXIT_FAILURE);
}
