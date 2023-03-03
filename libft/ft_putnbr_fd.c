/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 19:11:38 by lizhang       #+#    #+#                 */
/*   Updated: 2021/11/02 23:25:22 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_wrint(int fd, int n, size_t len)
{
	size_t	size;
	char	c;

	size = 1;
	while (len > 1)
	{
		size = size * 10;
		len --;
	}
	while (size > 1)
	{
		c = n / size % 10 + 48;
		size = size / 10;
		write(fd, &c, 1);
	}
	c = n % 10 + 48;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	len;
	int		nbuf;

	len = 1;
	nbuf = n;
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		while (nbuf <= -10 || nbuf >= 10)
		{
			nbuf = nbuf / 10;
			len++;
		}
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		ft_wrint(fd, n, len);
	}
}
