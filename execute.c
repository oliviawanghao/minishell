/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 18:27:39 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/19 16:09:21 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	g_e_code;

void	standard_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_e_code = 130;
	}
	if (signum == SIGQUIT)
	{
		write(1, "\n", 2);
		g_e_code = 131;
	}
}

void	parent_process_loop(t_shell *shell, \
t_token *current_token, int pipe_loc, pid_t last_child)
{
	struct sigaction	sa;
	char				buf[100];

	g_e_code = 0;
	sa.sa_handler = standard_sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	if (next_pipe(current_token))
	{
		close(shell->pipe[pipe_loc][1]);
		child_execute(shell, next_pipe(current_token), pipe_loc + 1, \
		shell->child);
	}
	if (pipe_loc == shell->n_pipe)
		waitpid(shell->child, &g_e_code, 0);
	else
		waitpid(shell->child, NULL, 0);
	if (pipe_loc > 0)
	{
		read(shell->pipe[pipe_loc - 1][0], buf, 100);
		kill(last_child, SIGUSR1);
	}
}

void	single_wait(t_shell *shell)
{
	struct sigaction	sa;

	sa.sa_handler = standard_sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	waitpid(shell->child, &g_e_code, 0);
	shell->lib->err[0] = WEXITSTATUS(g_e_code);
	if (g_e_code == 130 || g_e_code == 131)
		shell->lib->err[0] = g_e_code;
	else if (g_e_code == 2)
		shell->lib->err[0] = 130;
	else if (g_e_code == 3)
		shell->lib->err[0] = 131;
}

void	single_process(t_shell *shell, t_token *current_token)
{
	t_token	*prev;

	if (get_redirs(shell, current_token) == 1)
	{
		shell->lib->err[0] = 1;
		return ;
	}
	prev = current_token->prev;
	current_token = rm_redirect(current_token);
	expand_till_pipe(shell, current_token);
	if (prev)
		prev->next = current_token;
	else
		shell->tokens = current_token;
	shell->cmds = token_to_cmd(current_token);
	if (shell->cmds && isbuiltin_p(shell->cmds) == 1)
		shell->lib->err[0] = builtin_p(shell->cmds, shell->lib);
	else
	{
		fork_protected(shell);
		if (shell->child == 0)
			execute(shell, current_token, 0);
		else
			single_wait(shell);
	}
}

void	minishell(t_shell *shell)
{
	t_token	*current_token;

	pipe_prepare(shell);
	current_token = shell->tokens;
	if (current_token && syntax_error(current_token))
	{
		shell->lib->err[0] = 258;
		closepipes(shell);
		return ;
	}
	if (current_token && next_pipe(current_token) == NULL)
		single_process(shell, current_token);
	else if (current_token && next_pipe(current_token) != NULL)
	{
		child_execute(shell, current_token, 0, 0);
		waitpid(-1, NULL, 0);
		shell->lib->err[0] = WEXITSTATUS(g_e_code);
		if (g_e_code == 130 || g_e_code == 131)
			shell->lib->err[0] = g_e_code;
	}
	closepipes(shell);
}
