/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:59:38 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/27 08:21:57 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "stack.h"

int	set_char_state(char *s, t_char_state *char_state)
{
	char	q;
	int		len;

	q = is_quote(*s);
	len = 0;
	if (q != 0)
	{
		len = valid_quote(s, q);
		if (len > 0)
		{
			char_state->quote = q;
		}
	}
	return (len);
}

int	putchar_quote_state_zero(char *current, int fd)
{
	int	size;

	size = 0;
	if ((is_whitespace(*(current))))
		ft_putchar_fd(NONE, fd);
	else if (ft_ismeta((current)))
		ft_putchar_fd(ft_ismeta((current)), fd);
	else
		ft_putchar_fd(TEXT, fd);
	size++;
	return (size);
}

int	read_store_fd(int replace_fd, int quote_fd)
{
	int			i;
	struct stat	st;
	int			size;
	char		*buf;

	i = 0;
	fstat(quote_fd, &st);
	size = st.st_size;
	close(quote_fd);
	quote_fd = open("quote_fd", O_RDONLY, 0644);
	if (quote_fd == -1)
		printf("quotefd: %d\n", quote_fd);
	buf = malloc(sizeof(char) * size);
	read(quote_fd, buf, size);
	while (i < size)
	{
		ft_putchar_fd(buf[i], replace_fd);
		i++;
	}
	close(quote_fd);
	free(buf);
	unlink("quote_fd");
	return (size);
}

int	store_quote_seq(t_char_state *char_state, int len)
{
	int	quote_fd;
	int	i;

	i = 0;
	quote_fd = open("quote_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (i < len)
	{
		if (char_state->quote > 0)
		{
			if (char_state->quote == '\"' \
					&& ft_ismeta(&(char_state->current[i])) == DOLLAR)
				ft_putchar_fd(DOLLAR, quote_fd);
			else if (char_state->current[i] == char_state->quote)
				ft_putchar_fd(NONE, quote_fd);
			else
				ft_putchar_fd(TEXT, quote_fd);
		}
		i++;
	}
	return (quote_fd);
}

int	valid_quote(char *s, int quote)
{
	t_stack	stack;
	char	*ss;
	int		i;

	init_stack(&stack, NULL, 0);
	ss = s;
	push(&stack, ss);
	i = 1;
	while (is_emthy(&stack) == false && ss[i] != '\0')
	{
		if (is_quote(ss[i]) == quote)
			pop(&stack);
		i++;
	}
	if (is_emthy(&stack) == false && ss[i] == '\0')
	{
		pop(&stack);
		i = i * -1;
	}
	return (i);
}
