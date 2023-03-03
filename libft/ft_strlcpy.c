/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 18:19:12 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/01 22:16:54 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	count;

	count = 0;
	slen = ft_strlen(src);
	if (src[0] == 0)
		dst[0] = 0;
	if (dstsize > 0)
	{
		while (count < slen && count < (dstsize - 1))
		{
			dst[count] = src[count];
			count++;
		}
		dst[count] = 0;
	}
	return (slen);
}
