/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:55:43 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/23 17:26:18 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SIGNALS_H
# define SIGNALS_H

# include "main.h"

void	set_signal_fork(void);
void	before_readline(int signal);
void	set_signal(void *handler);
void	set_signal_cat_grep(void *handler);
void	set_signal_heredoc(void);
void	set_signal_fork_heredoc(void);

#endif