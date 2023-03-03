/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/31 19:44:18 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/19 16:18:26 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	free_one_token(t_token *token)
{
	free(token->value);
	free(token);
}

void	clearvarlist(t_list *lst)
{
	t_list	*listbuf;
	t_list	*buf;

	listbuf = lst;
	while (listbuf)
	{
		buf = listbuf;
		free_var_content(listbuf->content);
		listbuf = listbuf->next;
		free(buf);
	}
}

char	*substitute(char *ptr1, char *ptr2)
{
	char	*buf;

	buf = ptr1;
	ptr1 = ft_strdup(ptr2);
	free(buf);
	return (ptr1);
}
