/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:53:27 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/26 13:56:45 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "main.h"
# include "parse.h"

void	err_such(int exit, char *obj);
void	err_permission(int exit, char *obj);
void	err_exec(int exit, char *cmd_name);
void	err_syntax(int syntax_result);

#endif
