/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 22:10:17 by lizhang       #+#    #+#                 */
/*   Updated: 2021/07/04 23:52:21 by liwenzhan     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	size;
	int	count;

	size = ft_lstsize(lst);
	if (size == 1)
		return (lst);
	count = 1;
	while (count < size)
	{
		lst = lst->next;
		count++;
	}
	return (lst);
}
