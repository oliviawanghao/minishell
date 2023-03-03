/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 21:59:25 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/05 19:20:28 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ilen(int n)
{
	size_t	len;

	len = 1;
	while (n <= -10 || n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_istr(char	*dst, int n, int len)
{
	while (n > 0)
	{
		len--;
		dst[len] = n % 10 + 48;
		n = n / 10;
	}
	return (dst);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*a;

	len = ft_ilen(n);
	if (n < 0)
		len++;
	a = ft_calloc(len + 1, 1);
	if (a == NULL)
		return (NULL);
	if (n == 0)
		a[0] = '0';
	if (n == -2147483648)
		ft_strlcpy(a, "-2147483648", 12);
	else
	{
		if (n < 0)
		{
			a[0] = '-';
			n = -n;
		}
		a = ft_istr(a, n, len);
	}
	return (a);
}
