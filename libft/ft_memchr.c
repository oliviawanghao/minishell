/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 20:51:55 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/09 17:39:18 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			loc;
	unsigned char	c1;

	loc = 0;
	str = (unsigned char *)s;
	c1 = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (loc < n)
	{
		if (str[loc] == c1)
			return (str + loc);
		loc++;
	}
	return (NULL);
}
