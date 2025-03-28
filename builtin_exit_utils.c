/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:05:44 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/17 14:55:22 by hyeyeom          ###   ########.fr       */
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


int	check_input_range(char *arvs)
{
	int			z_cnt;
	int			length;
	long long	arv_atol;

	z_cnt = 0;
	if (arvs[0] == '-')
		z_cnt++;
	while (arvs[z_cnt] == '0')
		z_cnt++;
	length = ft_strlen(arvs);
	if (length == z_cnt)
		return (1); //모든 수가 0일때
	arv_atol = ft_atol(arvs);
    printf("%lld\n", arv_atol);
	if (ft_strlen(arvs + z_cnt) > 10)
        return (0); // 에러
	return (1);
}
