/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:59:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/04/04 14:18:22 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long long	ft_atol(char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	if (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (sign * res);
}

long long	ft_atol_length(char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	if (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		if (res > (LLONG_MAX - (*str - '0')) / 10)
				return (-1);
		res = res * 10 + *str - '0';
		str++;
	}
	return (1);
}

int	check_input_length(char *arvs)
{
	int			flag;
	int			z_cnt;
	int			length;
	long long	res;

	flag = 0;
	z_cnt = 0;
	if (arvs[0] == '-')
	{
		z_cnt++;
		flag = 1;
	}
	while (arvs[z_cnt] == '0')
		z_cnt++;
	length = ft_strlen(arvs);
	if (length == z_cnt)
		return (0);
	length = ft_strlen(&arvs[z_cnt]);
	if (flag == 1)
		length++;
	if ((length > 19 && flag == 0) || (length > 20 && flag == 1))
		return (-1);
	res = ft_atol_length(arvs);
	return (res);
}
