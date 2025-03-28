/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-1_mask.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:18:32 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/27 17:16:21 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"
#include "parse_step.h"
#include "stack.h"
#include "analysis.h"
#include "parse_utils.h"
#include "error.h"
#include "free.h"

int	handle_putchar(t_char_state *char_state, int fd)
{
	int	size;
	int	quote_fd;

	size = set_char_state(char_state->current, char_state);
	if (size < 0)
	{
		unlink("mask_fd");
		close(fd);
	}
	else if (size == 0)
		size = putchar_quote_state_zero(char_state->current, fd);
	else if (size > 0)
	{
		quote_fd = store_quote_seq(char_state, size);
		read_store_fd(fd, quote_fd);
	}
	return (size);
}

int	write_replace_spaces(char *s, int replace_fd)
{
	t_char_state	char_state;
	int				i;

	init_char_state(&char_state, s);
	i = 0;
	while (*(char_state.current) != '\0')
	{
		i = handle_putchar(&char_state, replace_fd);
		if (i > 0)
			char_state.current += i;
		else
			break ;
	}
	if (*(char_state.current) == '\0')
		ft_putchar_fd('\n', replace_fd);
	return (i);
}

char	*read_maskfd(int mask_fd, int *len)
{
	struct stat	st;
	char		*mask;

	fstat(mask_fd, &st);
	*len = (int)(st.st_size);
	if (*len == 0)
		return (NULL);
	mask = malloc(sizeof(char) * ((*len) + 1));
	ft_memset(mask, 0, (*len) + 1);
	read(mask_fd, mask, *len);
	return (mask);
}

char	*generate_mask(t_minish *sh)
{
	int		mask_fd;
	char	*mask;
	int		syntax_result;
	int		len;

	mask_fd = open("mask_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (mask_fd == -1 || write_replace_spaces(sh->src, mask_fd) < 0)
	{	
		sh->exitcode = 2;
		err_syntax(2);
		return (NULL);
	}
	close(mask_fd);
	mask_fd = open("mask_fd", O_RDONLY);
	mask = read_maskfd(mask_fd, &len);
	syntax_result = syntax_analysis(mask, &len);
	sh->mask = syntax_result2(sh, syntax_result, mask);
	close(mask_fd);
	unlink("mask_fd");
	return (mask);
}
