/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute4.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 17:50:57 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/03 17:45:38 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	fork_protected(t_shell *shell)
{
	shell->child = fork();
	if (shell->child == ((pid_t)-1))
	{
		perror("minishell: fork: ");
		exit(1);
	}
}

void	expand_till_pipe(t_shell *shell, t_token *current_token)
{
	if (current_token)
	{
		var_sub(current_token, shell->lib);
		expand_home(current_token);
	}
}
