/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 17:30:02 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/15 17:57:06 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
	{
		return (1);
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"' )
		return (1);
	return (0);
}

/*
在current_token后面添加一个token.
先新建一个new_token，
如果current_token为NULL，则直接返回new_token.
如果current_token不为空，则把二者连起来，再返回新的。
*/
t_token	*add_new_token(t_token *current_token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->len = 0;
	new_token->space = 1;
	new_token->type = -1;
	new_token->prev = NULL;
	new_token->next = NULL;
	if (current_token == NULL)
		return (new_token);
	else
	{
		current_token->next = new_token;
		new_token->prev = current_token;
		current_token = new_token;
	}
	return (current_token);
}
