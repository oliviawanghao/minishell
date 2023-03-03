/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/06 18:20:11 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/16 16:26:15 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	n;
	size_t	slen;
	char	*s1;
	char	c1;

	n = 0;
	c1 = (char) c;
	slen = ft_strlen(s);
	if (c1 == 0)
		return ((char *)s + slen);
	while (s[n] != c1 && s[n])
		n++;
	if (n >= slen)
		return (NULL);
	s1 = (char *)s + n;
	return (s1);
}
