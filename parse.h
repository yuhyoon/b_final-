/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:17:45 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/26 14:19:06 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"

typedef enum s_token
{
	NONE,
	TEXT,
	IN_RD,
	OUT_RD,
	DOLLAR,
	PIPE
}t_token;

typedef struct s_redrct
{
	char	*obj;
	int		fd;
	int		parts;
	int		access;
	char	type;
}t_redrct;

typedef struct s_char_state
{
	int		quote;
	int		quote_seq;
	char	*current;
}t_char_state;

typedef struct s_ready
{
	t_list		*text;
	t_list		*rdrct;
	int			rdrct_num;
	char		**cmd;
	t_redrct	*rdrct_in;
	t_redrct	*rdrct_out;
	int			num;
	int			input;
	int			output;
}t_ready;

#endif
