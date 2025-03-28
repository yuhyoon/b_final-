/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:11:32 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 09:21:44 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "parse.h"
# include "parse_utils.h"

//syntax
int			syntax_analysis(const char *m, int *len);
int			valid_meta(int token, char *mask);

//quote
int			valid_quote(char *s, int quote);
int			store_quote_seq(t_char_state *char_state, int len);
int			putchar_quote_state_zero(char *current, int fd);
int			read_store_fd(int fd, int quote_fd);
int			set_char_state(char *s, t_char_state *char_state);

//redirect
t_redrct	*init_rdrct(void);
int			create_rdrct(char *src, char *mask, t_list **head, int *sig_c);

//dollar
void		create_text_list(t_ready *rdy, char *src, char *mask, t_minish *sh);
int			get_variable(char *mask, char *src, t_list **head, t_minish *sh);
int			get_plain_text(char *s1, char *s2, char *src, t_list **head);
char		*valid_env(char *tmp, t_minish *sh);
int			count_text(char *mask);

//heredoc
void		handle_heredoc_child(int write_fd, char *delimeter);
void		handle_heredoc_parent(t_redrct *rdrct, int read_fd, \
int write_fd, int *sig_c);
void		create_heredoc_pipe(int *read_fd, int *write_fd);
void		f_heredoc(t_redrct *rdrct, int *sig_c);

//heredoc utils
void		restore_terminal(void);
void		close_fd(int fd);

#endif
