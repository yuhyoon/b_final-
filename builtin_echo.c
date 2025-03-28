/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:47:10 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/27 11:57:44 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "builtin.h"
#include "execution.h"
#include "child_process.h"

void	f_print_echo(char **param_list, int option_off)
{
	while (*param_list)
	{
		write(STDOUT_FILENO, *param_list, ft_strlen(*param_list));
		param_list++;
		if (*param_list)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!option_off)
		write(STDOUT_FILENO, "\n", 1);
}

int	f_check_n_option(char *is_option)
{
	int	i;
	int	len_option;

	i = 1;
	len_option = ft_strlen(is_option);
	if (len_option == 1 && is_option[0] != '=')
		return (0);
	while (is_option[0] == '-' && is_option[i] == 'n')
		i++;
	if (is_option[i] != '\0')
		return (0);
	return (1);
}

// typedef struct s_ready
// {
// 	t_list		*text;		//
// 	t_list		*rdrct;		//리다이렉션 정보
// 	int			rdrct_num;	//index
// 	char		**cmd;		// 명령어 갯수
// 	t_redrct	*rdrct_in;	//	받을때
// 	t_redrct	*rdrct_out;	// 	줄때
// 	int			num;		//total_number
// 	int			input;
// 	int			output;
// }t_ready;

// typedef struct s_child_process
// {
// 	int				num;
// 	t_child_state	state;
// 	int				*pp;
// 	char			**cmd;
// 	char			*exe_path;
// 	int				input_fd;
// 	int				output_fd;
// 	int				bulitin_code;
// }t_child_process;


unsigned int	f_echo(t_minish *sh, t_ready *rdy)

{
	char	**cmds;
	int		size;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	cmds = rdy->cmd;
	size = f_count_char(cmds);
	*f_exitcode() = 0;
	if (size == 1)
		write(STDOUT_FILENO, "\n", 1);
	else if (size > 1)
	{
		while (++i < size)
		{
			if (f_check_n_option(cmds[i]) == 1)
				flag = 1;
			else
				break ;
		}
		f_print_echo(&(cmds[i]), flag);
	}
	if (*f_exitcode() > 0)
		return (*f_exitcode());
	return (*f_exitcode());
}
