/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 22:14:55 by lizhang       #+#    #+#                 */
/*   Updated: 2021/09/25 15:19:05 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	result = ft_lstnew(f(lst->content));
	if (!result)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	temp = result;
	lst = lst->next;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&result, temp);
	}
	return (result);
}
