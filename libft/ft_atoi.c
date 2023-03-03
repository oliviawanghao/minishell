/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 17:40:40 by lizhang       #+#    #+#                 */
/*   Updated: 2021/11/02 23:21:57 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fneg(const char *str)
{
	int	c;

	c = 0;
	while (str[c] == 32 || (str[c] >= 8 && str[c] <= 14))
		c++;
	if (str[c] == 45)
		return (1);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	s;
	int	r;

	c = 0;
	s = 0;
	r = 0;
	while (str[c] == 32 || (str[c] >= 8 && str[c] <= 14))
		c++;
	if (str[c] == 45 || str[c] == 43)
		c++;
	s = c;
	while (ft_isdigit(str[c]))
		c++;
	while (s < c)
	{
		r = r * 10 - (str[s] - 48);
		s++;
	}
	r = ft_fneg(str) * r;
	return (r);
}
