/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 21:05:30 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/01 20:46:29 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;
	size_t			c;

	c = 0;
	d1 = (unsigned char *) s1;
	d2 = (unsigned char *) s2;
	if (s1 == s2 || n == 0)
		return (0);
	while (c < n && d1[c] == d2[c])
		c++;
	if (c == n)
		return (0);
	return ((d1[c]) - (d2[c]));
}
