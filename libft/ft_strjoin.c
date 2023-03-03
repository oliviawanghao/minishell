/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 18:59:56 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/03 14:51:29 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	count;
	size_t	count2;

	count = 0;
	if (!s1 || !s2)
		return (NULL);
	dst = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (!dst)
		return (NULL);
	while (s1[count++])
		dst[count - 1] = s1[count - 1];
	count2 = 0;
	while (s2[count2 ++])
	{
		dst[count - 1] = s2[count2 - 1];
		count++;
	}
	return (dst);
}
