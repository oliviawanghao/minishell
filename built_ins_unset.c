/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_unset.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 17:43:27 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/11 18:27:06 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
把unset的内容free掉。
*/
void	list_free_item(t_list *list)
{
	if (list)
	{
		if (list->content)
			free_var_content(list->content);
		free(list);
	}
	list = NULL;
}

/*
从list中找name，找到后用list_free_item()。
*/
t_list	*unset_in_list(char *name, t_list *list)
{
	t_var	*var;
	t_list	*buf;
	t_list	*buf2;

	var = findvar_in_list(name, list);
	buf = list;
	if (var && var->name && (t_var *)buf->content == var)
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
			return (list);
		}
		buf = buf->next;
	}
	return (list);
}

/*
如果要unset的不在envars里面，
再去other var里面找，并free掉。
*/
int	unset_var(char **name, t_lib *lib)
{
	int	i;

	i = 1;
	while (name[i])
	{
		lib->envars = unset_in_list(name[i], lib->envars);
		lib->ovars = unset_in_list(name[i], lib->ovars);
		lib->name_only = unset_in_list(name[i], lib->name_only);
		i++;
	}
	return (0);
}
