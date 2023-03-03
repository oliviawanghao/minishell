/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 18:58:49 by lizhang       #+#    #+#                 */
/*   Updated: 2023/01/18 18:14:49 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strsubcpy(char const *s, char *dst, size_t start, size_t len)
{
	size_t	count;
	char	*str;

	str = (char *)s;
	count = 0;
	while (count < len)
	{
		dst[count] = str[start + count];
		count++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		dst = ft_calloc(1, sizeof(char));
		if (!dst)
			return (NULL);
		return (dst);
	}
	if (len > slen - start)
		len = slen - start;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strsubcpy(s, dst, start, len);
	return (dst);
}
