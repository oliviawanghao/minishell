/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 19:42:32 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/01 20:52:54 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;
	size_t	dif;

	count = 0;
	if (!s1 && !s2)
		return (0);
	while (count < n)
	{
		dif = (unsigned char)s1[count] - (unsigned char)s2[count];
		if (dif != 0 || (!s1[count] && !s2[count]))
			break ;
		count++;
	}
	if (count == n)
		return (0);
	return (dif);
}
