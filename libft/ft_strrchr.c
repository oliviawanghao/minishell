/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/06 18:20:11 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/16 16:31:42 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	slen;
	char	*s1;
	char	c1;

	c1 = (char)c;
	slen = ft_strlen(s);
	while (s[slen] != c1 && slen > 0)
		slen--;
	if (s[0] == c1 && slen == 0)
		return ((char *)s);
	if (s[0] != c1 && slen == 0)
		return (NULL);
	s1 = (char *) s + slen;
	return (s1);
}
