/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:52:43 by yuhyoon           #+#    #+#             */
/*   Updated: 2025/03/26 13:52:44 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_H
# define DELETE_H

# include "parse.h"
# include "stack.h"

void	del_text(void *txt);
void	del_redrct(void *rd);
void	del_ready(void *ready);
void	del_stack(void *st);

#endif
