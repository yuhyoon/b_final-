/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:13:14 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/22 19:45:54 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_copy_envp(t_minish *sh, char **envp)
{
    int	i;
	
    sh->envp_count = f_count_char(envp);
	sh->envp = (char **)malloc(sizeof(char *) * (sh->envp_count + 1)); //main에서 받은 envps 저장
	if (!sh->envp)
		return (-1);
	i = -1;
	while (++i < (sh->envp_count))
	{
		sh->envp[i] = ft_strdup(envp[i]);
		if (!sh->envp[i])
		{
			while (--i >= 0)
				free(sh->envp[i]);
			free(sh->envp);
			exit(EXIT_FAILURE);
		}
	}
	sh->envp[sh->envp_count] = NULL; // NULL로 종료
	return (0);
}

int	init_envp(t_minish *sh, char **envp)
{
	sh->prev_for_pipe = -1;
	if (init_copy_envp(sh, envp) == -1)
		return (-1);
	f_init_env(sh->envp, &(sh->n_envs)); //env node
	f_sort_and_store_envp(sh->envp, &(sh->n_export));  //export node
	return (0);
}
