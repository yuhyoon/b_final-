/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:01:55 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/28 09:03:38 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "main.h"

void	dengling(void *content, int size_type);
void	free_minish(t_minish *minish);
void	free_str_array(char **arr);
void	free_envps(t_envp **node);
void	free_init_envps(t_minish *sh);

#endif
