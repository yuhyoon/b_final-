/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_step-0_blank.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:18:27 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/11 02:56:37 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*check_blank(char *start, char *end)
{
	int	i;
	int	len;

	i = 0;
	len = end - start;
	while (i < len && start[i] == 0)
	{
		i++;
	}
	if (i == len)
		return (start);
	return (NULL);
}

/*
char	*check_replace(t_minish *sh);
char	*replace_dollar_to_text(t_minish *sh, int i);
void	mask_regenerate(t_minish *sh, t_list *lst);
char	*putchar_replace(t_minish *sh, t_list *lst, int	fd)

char	*check_replace(t_minish *sh)
{
	int	i;
	int	len;
	t_list *lst;

	i = 0;
	len = ft_strlen_delim(sh->mask, '\n');
	lst = NULL;
	while (i < len)
	{
		if (sh->src[i] == DOLLAR)
			lst = ft_lstadd_back( \
			ft_lstnew(replace_dollar_to_text(sh, i)), &lst);
		i++;
	}
	if (lst != NULL)
	{
		sh->mask = mask_regenerate(sh, lst);
	}
}

char	*replace_dollar_to_text(t_minish *sh, int i)
{
	char	*txt;

	txt = get_variable(sh->mask, sh->src, sh);
	return (txt);
}

void	mask_regenerate(t_minish *sh, t_list *lst);
{
	int				remask_fd;
	t_char_state	char_state;
	char			*mask_regnrte;

	remask_fd = open("remask_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	init_char_state(&char_state, sh->mask);
	mask_regnrte = putchar_replace(sh, lst);
	unlink("remask_fd");
	close(remask_fd);
	return (mask_regnrte);
}

char	*putchar_replace(t_minish *sh, t_list *lst, int	fd)
{
	int		i;
	char	*env_value;
	int		len;
	char	*replace_str;

	i = 0;
	while (sh->mask[i] != '\n')
	{
		write(fd, &sh->mask[i], 1);
		if (sh->mask[i] == DOLLAR)
		{
			env_value = (char *)lst->content;
			if (*env_value == '\0' && \
			(sh->mask[i + 1] == 0 || mask[i + 1] == '\n'))
				write(fd, "1", 1);
			else
				write(fd, env_value, ft_strlen(env_value));
			i += ft_strlen(&sh->mask[i]);
		}
		else
			i++;
	}
	replace_str = read_maskfd(fd, &len);
	return (replace_str);
}
*/
