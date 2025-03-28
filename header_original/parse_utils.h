/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:18:12 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/27 08:18:45 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "parse.h"

int		ft_strlen_delim(char *s, char delim);
void	init_char_state(t_char_state *state, char *s);
int		is_whitespace(char c);
int		is_quote(char c);
int		ft_ismeta(char *input);
char	*syntax_result2(t_minish *sh, int result, char *mask);

#endif
