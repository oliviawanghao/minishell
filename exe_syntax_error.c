/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_syntax_error.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 18:13:39 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/15 18:04:02 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	put_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", STDERR);
	if (token == NULL)
		ft_putstr_fd("newline", STDERR);
	else if (token->value[0] == '|')
		ft_putchar_fd(token->value[0], STDERR);
	else if (token->len > 2)
	{
		ft_putchar_fd(token->value[0], STDERR);
		ft_putchar_fd(token->value[1], STDERR);
	}
	else
		ft_putstr_fd(token->value, STDERR);
	ft_putendl_fd("\'", STDERR);
	return (258);
}

int	put_syntax_end(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", STDERR);
	return (258);
}

int	syntax_error(t_token *tokens)
{
	t_token	*current_token;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == PIPE && !current_token->prev && \
		!current_token->next)
			return (put_syntax_error(current_token));
		if (current_token->type == PIPE && current_token->prev && \
		!current_token->next)
			return (put_syntax_end());
		if (current_token->type == UNKNOWN)
			return (put_syntax_error(current_token));
		if (current_token->type == GREAT || current_token->type == GREATGREAT
			|| current_token->type == LESS || current_token->type == LESSLESS)
		{
			if (current_token->next == NULL)
				return (put_syntax_error(NULL));
			current_token = current_token->next;
			if (current_token->type > LITERAL)
				return (put_syntax_error(current_token));
		}
		current_token = current_token->next;
	}
	return (0);
}
