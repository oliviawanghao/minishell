/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 17:47:36 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/13 15:36:10 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
如果token的type是expansion，则需要把value根据空格拆分成不同的cmd
*/
int	expansion_cmd_count(char *value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (value[i])
	{
		while (is_space(value[i]))
			i++;
		count++;
		while (value[i] && !is_space(value[i]))
			i++;
	}
	return (count);
}

/*
数当前pipe中cmd的个数。
如果是LITERAL，如果中间有空格，则一定是被替换过的，那么一定是要拆分的。
if (current_token->space == 0)就贴在前面。
*/
int	get_cmd_count(t_token *tokens)
{
	t_token	*current_token;
	int		i;

	i = 0;
	current_token = tokens;
	while (current_token && current_token->value \
	&& current_token->type != PIPE)
	{
		if (current_token->space == 0)
			i += 0;
		else
		{
			if (current_token->type == LITERAL)
				i += expansion_cmd_count(current_token->value);
			else
				i++;
		}
		current_token = current_token->next;
	}
	return (i);
}

int	get_expansion_cmd(char *value, char **cmds, int i)
{
	char	**expansion_cmd;
	int		j;

	expansion_cmd = ft_space_split(value);
	j = 0;
	while (expansion_cmd[j])
	{
		cmds[i] = expansion_cmd[j];
		i++;
		j++;
	}
	free(expansion_cmd);
	return (i);
}

void	get_cmd(t_token *current_token, char **cmds)
{
	int	i;

	i = 0;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->space == 0)
		{
			i--;
			cmds[i] = join_free(cmds[i], current_token->value);
			i++;
		}
		else
		{
			if (current_token->type == LITERAL)
				i = get_expansion_cmd(current_token->value, cmds, i);
			else
				cmds[i++] = ft_strdup(current_token->value);
		}
		current_token = current_token->next;
	}
}

/*
把token变成cmd，**char。
现在的token->type只有可能是	SINGLE_QUOTE, DOUBLE_QUOTE, EXPANSION, LITERAL
export ls="ls -l"之后，再"$ls"
因为"$ls"的type是DOUBLE_QUOTE，所以不需要把ls -l拆分。
*/
char	**token_to_cmd(t_token *tokens)
{
	t_token	*current_token;
	char	**cmds;
	int		cmd_count;

	if (!tokens || tokens == NULL)
		return (NULL);
	cmd_count = get_cmd_count(tokens);
	if (cmd_count == 0)
		return (NULL);
	cmds = malloc(sizeof(char *) * (cmd_count + 1));
	if (!(cmds))
		return (NULL);
	current_token = tokens;
	get_cmd(current_token, cmds);
	cmds[cmd_count] = NULL;
	return (cmds);
}
