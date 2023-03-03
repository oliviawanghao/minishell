/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 17:49:58 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/09 17:46:28 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	count;
	char	*str;

	str = (char *)s;
	count = 0;
	while (count < n)
	{
		str[count] = 0;
		count++;
	}
}
