/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/06 18:41:58 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/01 20:53:49 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	n;

	n = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		while (n < len)
		{
			*(char *)(dst + n) = *(char *)(src + n);
			n++;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			*(char *)(dst + len) = *(char *)(src + len);
		}
	}
	return (dst);
}
