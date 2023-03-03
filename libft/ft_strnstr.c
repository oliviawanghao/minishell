/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 21:42:32 by lizhang       #+#    #+#                 */
/*   Updated: 2021/11/02 23:23:46 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_findstr(char *s1, char *s2, size_t n)
{
	size_t	count1;
	size_t	count2;

	count1 = 0;
	while (count1 < n && s1[count1] != 0)
	{
		count2 = 0;
		while (s1[count1 + count2] == s2[count2] && \
				s2[count2] && count1 + count2 < n)
			count2++;
		if (s2[count2] == 0)
			return (count1);
		count1++;
	}
	return (n);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*d1;
	char	*d2;
	size_t	loc;

	d1 = (char *)s1;
	d2 = (char *)s2;
	if (ft_strlen(d2) == 0)
		return (d1);
	loc = ft_findstr(d1, d2, n);
	if (loc == n)
		return (NULL);
	d1 = d1 + loc;
	return (d1);
}
