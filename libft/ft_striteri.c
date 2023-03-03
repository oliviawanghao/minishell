/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 12:45:03 by lizhang       #+#    #+#                 */
/*   Updated: 2021/08/12 13:06:11 by liwenzhan     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	count;

	count = 0;
	if (!s)
		return ;
	while (s[count])
	{
		f(count, &s[count]);
		count++;
	}
}
