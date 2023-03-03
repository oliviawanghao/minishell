/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 17:31:11 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/19 15:26:35 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
free一个**char
*/
void	cleardarray(char **array)
{
	int	count;

	count = 0;
	if (!array || array == NULL)
		return ;
	while (array[count])
	{
		free(array[count]);
		count++;
	}
	if (array)
		free(array);
}

void	clearpipe(int **pipe, int len)
{
	int			i;
	struct stat	info;

	i = 0;
	while (pipe && i < len)
	{
		if (fstat(pipe[i][0], &info) == 0)
			close(pipe[i][0]);
		if (fstat(pipe[i][1], &info) == 0)
			close(pipe[i][1]);
		free (pipe[i]);
		i++;
	}
	if (pipe)
		free(pipe);
}

void	cleartokens(t_token *token)
{
	t_token	*buf;

	if (token == NULL)
		return ;
	while (token != NULL)
	{
		buf = token;
		token = token->next;
		if (buf->value)
			free(buf->value);
		free(buf);
	}
}

void	free_var_content(void *item)
{
	if (!item)
		return ;
	if (((t_var *)item)->name)
		free(((t_var *)item)->name);
	if (((t_var *)item)->data)
		free(((t_var *)item)->data);
	free(item);
}

void	clearshell(t_shell *shell)
{
	if (shell->cmds)
		cleardarray(shell->cmds);
	if (shell->tokens)
		cleartokens(shell->tokens);
	if (shell->delimiter)
		free(shell->delimiter);
	free(shell);
}
