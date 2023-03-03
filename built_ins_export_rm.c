/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_export_rm.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/18 18:57:18 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/03 18:01:24 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

t_list	*rm_from_list(char *name, t_list *list)
{
	t_var	*var;
	t_list	*buf;
	t_list	*buf2;

	var = findvar_in_list(name, list);
	buf = list;
	if (list && list->content && var && (t_var *)buf->content == var)
	{
		list = list->next;
		list_free_item(buf);
		return (list);
	}
	while (var && buf && buf->next)
	{
		if ((t_var *)buf->next->content == var)
		{	
			buf2 = buf->next;
			buf->next = buf->next->next;
			list_free_item(buf2);
		}
		buf = buf->next;
	}
	return (list);
}
