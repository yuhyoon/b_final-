/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-1_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:18:37 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_delim(char *s, char delim)
{
	int	i;

	i = 0;
	while (s[i] != delim)
	{
		i++;
	}
	return (i);
}

void	init_char_state(t_char_state *state, char *s)
{
	state->current = s;
	state->quote = 0;
	state->quote_seq = -1;
}

int	is_whitespace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ' )
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'')
		return ('\'');
	else if (c == '\"')
		return ('\"');
	return (0);
}

int	ft_ismeta(char *input)
{
	if (*input == '<')
		return (IN_RD);
	else if (*input == '>')
		return (OUT_RD);
	else if (*input == '$')
		return (DOLLAR);
	else if (*input == '|')
		return (PIPE);
	else
		return (0);
}
