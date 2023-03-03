/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 17:29:40 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/11 16:21:32 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
非quote的情况，遇到space或者symbol，就停止。
需要考虑export ls="ls -l"的情况: symbol是引号，且该symbol前一个是=
最后返回去掉引号之后的长度。
*/
int	get_literal_len(char *input_value, int i)
{
	int	x;
	int	len;

	x = i;
	len = 0;
	while (input_value[x] && !is_space(input_value[x]) && \
	!is_symbol(input_value[x]) && !is_quote(input_value[x]))
	{
		len++;
		x++;
	}
	return (len);
}

/*
直到找到下一个同类quote，
从quote的后一个字符开始算长度。
*/
int	get_quote_len(char *input_value, int i)
{
	int	x;
	int	len;

	x = i + 1;
	len = 0;
	while (input_value[x] && input_value[x] != input_value[i])
	{
		len++;
		x++;
	}
	return (len);
}

/*
只要是同类的symbol，就放在同一个token中。
如>>>>>>,或||||||||||，都放在同一个token中。
*/
int	get_symbol_len(char *input_value, int i)
{
	int	x;
	int	len;

	x = i;
	len = 0;
	while (input_value[x] && input_value[x] == input_value[i])
	{
		len++;
		x++;
	}
	return (len);
}

int	get_length(t_token *current_token, char *input_value, int i)
{
	int		len;

	if (current_token->type == LITERAL)
		len = get_literal_len(input_value, i);
	else if (current_token->type == SINGLE_QUOTE || \
	current_token->type == DOUBLE_QUOTE)
		len = get_quote_len(input_value, i);
	else
		len = get_symbol_len(input_value, i);
	return (len);
}

/*
先得到每一个token的len，再malloc value 的 len。
再根据len，通过while loop，一个一个给value赋值。
*/
void	get_value(t_token *current_token, char *input_value, int i)
{
	int		j;
	int		len;
	char	*value;

	len = get_length(current_token, input_value, i);
	value = malloc(sizeof(char) * (len + 1));
	j = 0;
	if (current_token->type == SINGLE_QUOTE || \
	current_token->type == DOUBLE_QUOTE)
		i++;
	while (j < len)
	{
		value[j] = input_value[i + j];
		j++;
	}
	value[len] = '\0';
	current_token->len = len;
	current_token->value = value;
}
