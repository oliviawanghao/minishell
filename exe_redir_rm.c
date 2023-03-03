/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_redir_rm.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/06 16:36:06 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/03 17:57:16 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	redir_first_last(t_token *temp1)
{
	if (temp1->prev)
		temp1->prev->next = NULL;
}

t_token	*redir_first(t_token *head, t_token *tokens)
{
	t_token	*temp1;
	t_token	*temp2;

	temp1 = tokens;
	temp2 = tokens->next;
	if (temp2->next)
	{
		if (temp1->prev)
		{
			temp2->next->prev = temp1->prev;
			temp1->prev->next = temp2->next;
		}
		else
			temp2->next->prev = NULL;
		tokens = temp2->next;
		head = tokens;
	}
	else
	{
		redir_first_last(temp1);
		tokens = NULL;
	}
	free_one_token(temp1);
	free_one_token(temp2);
	return (tokens);
}

/*
if:要被去掉的redir出现在该pipe的开头
else:被去掉的redir前面还有其他literal
*/
t_token	*redir_last(t_token *head, t_token *tokens)
{
	t_token	*temp1;
	t_token	*temp2;

	temp1 = tokens;
	temp2 = tokens->next;
	if (temp1 == head)
	{
		free_one_token(temp1);
		free_one_token(temp2);
		return (NULL);
	}
	else
	{
		if (head == tokens)
			head = NULL;
		tokens->prev->next = NULL;
		free_one_token(temp1);
		free_one_token(temp2);
		return (head);
	}
}

t_token	*redir_middle(t_token *head, t_token *tokens)
{
	t_token	*temp1;
	t_token	*temp2;

	temp1 = tokens;
	temp2 = tokens->next;
	temp1->prev->next = temp2->next;
	temp2->next->prev = temp1->prev;
	tokens = temp2->next;
	if (temp1 == head)
		head = tokens;
	free_one_token(temp1);
	free_one_token(temp2);
	return (tokens);
}

t_token	*rm_redirect(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	while (tokens && tokens->next && tokens->type != PIPE)
	{
		if (is_redirect(tokens->type) == 1)
		{
			if (tokens->prev == NULL || tokens->prev->type == PIPE)
			{
				tokens = redir_first(head, tokens);
				head = tokens;
			}
			else if (tokens->next->next == NULL)
				return (redir_last(head, tokens));
			else
				tokens = redir_middle(head, tokens);
		}
		else
			tokens = tokens->next;
	}
	if (head == NULL)
		return (NULL);
	return (head);
}
