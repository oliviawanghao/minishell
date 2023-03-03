/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 22:13:46 by lizhang       #+#    #+#                 */
/*   Updated: 2021/07/05 12:28:03 by liwenzhan     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lstmove;

	while (*lst)
	{
		lstmove = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lstmove;
	}
	*lst = NULL;
}
