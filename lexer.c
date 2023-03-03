/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 15:55:29 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/19 15:28:10 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
得到非LITERAL类型token的type。
如果是>>>>>,或者<<<<<<<<，或<<<&&&&，则返UNKNOWN。
*/
void	get_type(t_token *current_token, char *input_value, int i)
{
	get_value(current_token, input_value, i);
	if (!ft_strcmp(current_token->value, "<"))
		current_token->type = LESS;
	else if (!ft_strcmp(current_token->value, "<<"))
		current_token->type = LESSLESS;
	else if (!ft_strcmp(current_token->value, ">"))
		current_token->type = GREAT;
	else if (!ft_strcmp(current_token->value, ">>"))
		current_token->type = GREATGREAT;
	else if (!ft_strcmp(current_token->value, "|"))
		current_token->type = PIPE;
	else
		current_token->type = UNKNOWN;
}

/*
处理single or double quote
*/
int	handle_symbol(t_token *current_token, char *input_value, int i)
{
	get_type(current_token, input_value, i);
	if (i > 0 && !is_space(input_value[i - 1]))
		current_token->space = 0;
	i += current_token->len;
	return (i);
}

/*
处理literal，包扩可能包含export ls="ls -l"的情况。
//2023-02-11更新：把两种quote都看成一种特殊的literal，不当作symbol来处理。
*/
int	handle_literal(t_token *current_token, char *input_value, int i)
{
	if (is_quote(input_value[i]))
	{
		if (input_value[i] == '\'')
			current_token->type = SINGLE_QUOTE;
		else
			current_token->type = DOUBLE_QUOTE;
		if (i > 0 && (!is_symbol(input_value[i - 1]) && \
		!is_space(input_value[i - 1])))
			current_token->space = 0;
		get_value(current_token, input_value, i);
		i += current_token->len + 2;
	}
	else
	{
		current_token->type = LITERAL;
		get_value(current_token, input_value, i);
		if (i > 0 && (!is_symbol(input_value[i - 1]) && \
		!is_space(input_value[i - 1])))
			current_token->space = 0;
		i += current_token->len;
	}
	return (i);
}

void	tokens_create(t_token *current_token, char *input_value, int i)
{
	while (input_value[i])
	{
		if (is_space(input_value[i]))
		{
			while (is_space(input_value[i]))
				i++;
			if (input_value[i] && (int)(current_token->type) != -1)
				current_token = add_new_token(current_token);
		}
		else if (is_symbol(input_value[i]))
		{
			i = handle_symbol(current_token, input_value, i);
			if (input_value[i] && !is_space(input_value[i]))
				current_token = add_new_token(current_token);
		}
		else
		{
			i = handle_literal(current_token, input_value, i);
			if (input_value[i] && !is_space(input_value[i]))
				current_token = add_new_token(current_token);
		}
	}
}

t_token	*lexer(char *input)
{
	int		i;
	char	*input_value;
	t_token	*tokens;
	t_token	*current_token;

	input_value = ft_strdup(input);
	current_token = NULL;
	current_token = add_new_token(current_token);
	tokens = current_token;
	i = 0;
	tokens_create(current_token, input_value, i);
	free(input_value);
	return (tokens);
}
