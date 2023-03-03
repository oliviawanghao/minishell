/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 19:06:29 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/16 16:23:24 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	dlen;
	size_t	c;

	c = 0;
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (dstsize > 0)
	{
		while (src[c] && dlen + c < dstsize - 1)
		{
			dst[dlen + c] = src[c];
			c++;
		}
		if (dlen + c <= dstsize)
			dst[dlen + c] = 0;
	}
	if (dlen < dstsize)
		return (slen + dlen);
	return (slen + dstsize);
}
