/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/05 19:33:54 by lizhang       #+#    #+#                 */
/*   Updated: 2023/01/06 16:53:56 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

t_token	*next_pipe(t_token *current_token)
{
	t_token	*buf;

	if (!current_token)
		return (NULL);
	buf = current_token;
	while (buf && buf->next && buf->type != PIPE)
		buf = buf->next;
	buf = buf->next;
	return (buf);
}

int	count_pipes(t_token *token)
{
	t_token	*current_token;
	int		n_pipe;

	n_pipe = 0;
	current_token = token;
	while (current_token && next_pipe(current_token) != NULL)
	{
		current_token = next_pipe(current_token);
		n_pipe++;
	}
	return (n_pipe);
}

void	pipe_prepare(t_shell *shell)
{
	int	i;

	i = 0;
	shell->n_pipe = count_pipes(shell->tokens);
	shell->pipe = (int **)malloc((shell->n_pipe + 1) * sizeof(int *));
	while (i <= shell->n_pipe)
	{
		shell->pipe[i] = malloc(sizeof(int) * 2);
		pipe(shell->pipe[i]);
		i++;
	}
}
