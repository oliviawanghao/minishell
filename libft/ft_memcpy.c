/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 18:22:56 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/01 21:02:23 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	if (!dst && !src)
		return (NULL);
	while (count < n)
	{
		*(char *)(dst + count) = *(char *)(src + count);
		count++;
	}
	return (dst);
}
