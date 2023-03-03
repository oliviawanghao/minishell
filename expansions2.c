/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansions2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/06 17:23:24 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/15 18:50:25 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

char	*combine(t_list *words)
{
	t_list	*buf;
	char	*str;

	buf = words;
	str = ft_strdup("");
	while (buf)
	{
		if (((t_var *)buf->content)->data)
			str = join_free(str, ((t_var *)buf->content)->data);
		buf = buf->next;
	}
	return (str);
}

static int	fill_name(char *str, t_var *var, int i)
{
	int	j;

	j = i;
	i++;
	if (str[i] && str[i] == '?')
		i++;
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	var->name = ft_substr(str, j + 1, i - 1 - j);
	var->data = NULL;
	return (i);
}

t_list	*get_var_name(char *str, int i, int j)
{
	t_var	*var;
	t_list	*words;

	i = 0;
	words = NULL;
	while (str && str[i])
	{
		j = i;
		var = (t_var *)malloc(sizeof(t_var));
		if (!var)
			mallocerr();
		if (str[i] == '$' && str[i + 1] != 0)
			i = fill_name(str, var, i);
		else if (str[i] != '$' || (str[i] == '$' && str[i + 1] == 0))
		{
			if (str[i] == '$')
				i++;
			while (str[i] && str[i] != '$')
				i++;
			var->data = ft_substr(str, j, i - j);
			var->name = NULL;
		}
		ft_lstadd_back(&words, ft_lstnew((void *)var));
	}
	return (words);
}

void	single_token_sub(t_token *current_token, t_lib *lib)
{
	t_list	*words;
	t_list	*words_start;
	void	*found;
	char	*buf;

	words = get_var_name(current_token->value, 0, 0);
	words_start = words;
	while (words && words->content)
	{
		if (((t_var *)words->content)->name && \
		((char *)((t_var *)words->content)->name)[0] == '?')
			((t_var *)words->content)->data = ft_itoa(lib->err[0]);
		else if (((t_var *)words->content)->name)
		{
			found = findvar(((t_var *)words->content)->name, lib);
			if (found)
				((t_var *)words->content)->data = \
				ft_strdup((char *)((t_var *)found)->data);
		}
		words = words->next;
	}
	buf = current_token->value;
	current_token->value = combine(words_start);
	free(buf);
	clearvarlist(words_start);
}

void	var_sub(t_token *tokens, t_lib *lib)
{
	t_token	*current_token;

	current_token = tokens;
	while (current_token && current_token->type != PIPE)
	{
		if (ft_strncmp("$", current_token->value, 2) != 0 && \
		current_token->type != SINGLE_QUOTE && \
		finddollar(current_token->value) > 0)
			single_token_sub(current_token, lib);
		current_token = current_token->next;
	}
}
