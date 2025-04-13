/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:21:22 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/04/14 00:38:35 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minish(t_minish *sh, char **envp)
{
	int	result;

	sh->envp = NULL;
	sh->built_code = 0;
	ft_memset(sh, 0, sizeof(t_minish));
	sh->save_in = STDIN_FILENO;
	sh->save_out = STDOUT_FILENO;
	if (!envp)
		return ;
	result = init_envp(sh, envp);
	if (result == -1)
		return ;
}

int	read_input(t_minish *sh)
{
	char	*input;

	input = readline("minishell> ");
	if (input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (0);
	}
	else if (ft_strlen(input) == 0)
	{
		free(input);
		return (2);
	}
	sh->src = ft_strdup(input);
	add_history(sh->src);
	free(input);
	sh->parse_sig = 0;
	return (1);
}

void	parent_proccess(t_minish *sh, t_ready *rdy, pid_t pid, int *pp)
{
	set_signal_cat_grep(after_cat_grep);
	if (sh->child_pids != NULL)
		sh->child_pids[rdy->num - 1] = pid;
	if (sh->prev_for_pipe != -1)
		close(sh->prev_for_pipe);
	if (sh->cmd_count > 1 && rdy->num < sh->cmd_count)
	{
		close(pp[1]);
		sh->prev_for_pipe = pp[0];
	}
}

pid_t	create_process(t_ready *rdy, t_minish *sh)
{
	pid_t	pid;
	int		result;
	int		pp[2];

	set_signal_fork();
	if (rdy->num < sh->cmd_count)
		pipe(pp);
	if (*(rdy->cmd) == NULL)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		set_signal_cat_grep(before_cat_grep);
		result = child_process(rdy, pp, sh);
		free_all_envps(sh);
		free_minish(sh);
		exit(result);
	}
	else
		parent_proccess(sh, rdy, pid, pp);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minish	sh;
	int			res;

	set_signal(before_readline);
	if (ac > 1)
		exit(EXIT_FAILURE);
	init_minish(&sh, envp);
	while (ac == 1 && av[0])
	{
		res = read_input(&sh);
		if (!res)
			break ;
		if (res == 1)
		{
			if (!generate_mask(&sh) || \
				parsing(&sh, ft_strlen_delim(sh.mask, '\n')) != \
				ft_strlen_delim(sh.mask, '\n'))
				free_minish(&sh);
			else
				execute(&sh);
		}
	}
	free_all_envps(&sh);
	rl_clear_history();
	return (0);
}
