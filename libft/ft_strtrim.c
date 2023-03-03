/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 19:01:48 by lizhang       #+#    #+#                 */
/*   Updated: 2021/11/02 23:23:20 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charinset(const char *set, char c)
{
	size_t	n;

	n = 0;
	while (set[n])
	{
		if (set[n] == c)
			return (1);
		n++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	count;
	size_t	cstart;
	size_t	cend;

	if (!s1 || !set)
		return (NULL);
	cstart = 0;
	count = 0;
	while (ft_charinset(set, s1[cstart]) && s1[cstart])
		cstart++;
	cend = ft_strlen(s1);
	while (cend > cstart && ft_charinset(set, s1[cend - 1]))
		cend--;
	dst = ft_calloc((cend - cstart + 1), 1);
	if (!dst)
		return (NULL);
	while (cstart < cend)
	{
		dst[count] = s1[cstart];
		count++;
		cstart++;
	}
	return (dst);
}
