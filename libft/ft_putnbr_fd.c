/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:29:52 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/11 20:07:01 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		i = i * 10;
		n = n / 10;
	}
	return (i);
}

static void	print_nbr(int n_size, int n, int fd, int flag)
{
	int	x;

	if (flag < 0)
		write (fd, "-", 1);
	while (n_size != 0)
	{
		x = (n / n_size);
		n = n - (x * n_size);
		x = x + '0';
		n_size = n_size / 10;
		write (fd, &x, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		n = n * -1;
		print_nbr(get_size(n), n, fd, -1);
	}
	else if (n >= 0)
		print_nbr(get_size(n), n, fd, 0);
}
