/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_redir_get.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 17:48:59 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/06 15:43:09 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	open_failed(char *value)
{
	if (access(value, F_OK) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(value, STDERR);
		ft_putendl_fd(": Permission denied", STDERR);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(value, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
	}
}

void	openfile(t_shell *shell, char *value, int type)
{
	if (type == GREAT)
		shell->f_out = open(value, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type == GREATGREAT)
		shell->f_out = open(value, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else
		shell->f_in = open(value, O_RDONLY, S_IRWXU);
	if (((type == GREAT || type == GREATGREAT) && shell->f_out == -1)
		|| (type == LESS && shell->f_in == -1))
		open_failed(value);
	return ;
}

void	is_heredoc(t_shell *shell, t_token *current_token)
{
	shell->heredoc_on = 1;
	shell->delimiter = ft_strdup(current_token->next->value);
}

int	get_redirs(t_shell *shell, t_token *tokens)
{
	t_token	*current_token;

	current_token = tokens;
	shell->f_in = 0;
	shell->f_out = 1;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == GREAT || current_token->type == GREATGREAT
			|| current_token->type == LESS)
		{
			current_token = current_token->next;
			openfile(shell, current_token->value, current_token->prev->type);
			if (shell->f_in == -1 || shell->f_out == -1)
				return (1);
		}
		if (current_token->type == LESSLESS)
			is_heredoc(shell, current_token);
		current_token = current_token->next;
	}
	return (0);
}

int	is_redirect(int type)
{
	if (type == GREAT || type == GREATGREAT || type == LESS || type == LESSLESS)
		return (1);
	return (0);
}
