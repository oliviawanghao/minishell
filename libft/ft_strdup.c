/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 20:56:46 by lizhang       #+#    #+#                 */
/*   Updated: 2023/01/15 19:49:19 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	i = 0;
	while (src[i])
	{
		i++;
	}
	dup = (char *)malloc(i + 1);
	if (!dup)
		return (0);
	dup[i] = 0;
	while (i > 0)
	{
		i--;
		dup[i] = src[i];
	}
	return (dup);
}
