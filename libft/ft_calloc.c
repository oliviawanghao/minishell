/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 20:25:19 by lizhang       #+#    #+#                 */
/*   Updated: 2022/09/28 21:25:59 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*p;

	p = (void *) malloc (num * size);
	if (p == NULL)
		return (NULL);
	ft_bzero (p, num * size);
	return (p);
}
