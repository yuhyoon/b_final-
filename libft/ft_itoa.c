/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:45:11 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/28 16:28:12 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(long long n)
{
	long long	digit;

	if (n < 0)
		n = n * -1;
	digit = 1;
	while (n > 9)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

static int	get_size_int(long long n)
{
	long long	size;

	size = 1;
	if (n < 0)
		n = n * -1;
	while (n > 9)
	{
		size = size * 10 ;
		n = n / 10;
	}
	return (size);
}

static void	insert_char(char *result, \
long long digit, long long n, size_t size_n)
{
	if (n < 0)
	{
		*result = '-';
		result = result + 1;
		n = n * -1;
	}
	while (digit)
	{
		*result = (n / size_n) + '0';
		n = n - ((n / size_n) * size_n);
		digit--;
		size_n = size_n / 10;
		result++;
	}
	*result = '\0';
}

char	*ft_itoa(int n)
{
	long long	digit;
	char		*result;
	size_t		size_n;
	char		*result_start;
	long long	nn;

	nn = (long long)n;
	digit = count_digit(nn);
	if (nn < 0)
		result = (char *)malloc(sizeof(char) * digit + 2);
	else
		result = (char *)malloc(sizeof(char) * digit + 1);
	if (!result)
		return (0);
	result_start = result;
	size_n = get_size_int(nn);
	insert_char(result, digit, nn, size_n);
	return (result_start);
}
