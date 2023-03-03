/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute3.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/06 19:49:44 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/10 19:21:14 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	child(t_shell *shell, t_token *current_token, int pipe_loc)
{
	t_list	*envar;
	t_token	*tokenbuf;

	signal(SIGUSR1, &sighandler);
	tokenbuf = current_token;
	envar = (t_list *)(shell->lib)->envars;
	if (shell->f_in != STDIN_FILENO)
		dup2(shell->f_in, STDIN_FILENO);
	else if (shell->heredoc_on == 1)
		write_heredoc(shell);
	else if (pipe_loc > 0)
		dup2(shell->pipe[pipe_loc - 1][0], STDIN_FILENO);
	if (shell->f_out != STDOUT_FILENO)
		dup2(shell->f_out, STDOUT_FILENO);
	else if (next_pipe(current_token) != NULL)
		dup2(shell->pipe[pipe_loc][1], STDOUT_FILENO);
	if (shell->cmds && isbuiltin_c(shell->cmds) == 1)
		builtin_c(shell->cmds, shell->lib);
	else if (shell->cmds)
		exe(duplist(envar), shell->cmds);
	exit(0);
}

void	execute(t_shell *shell, t_token *current_token, int loc_pipe)
{
	int	err;

	shell->cmds = token_to_cmd(current_token);
	if (shell->cmds && shell->cmds[0])
		test_exe(shell->cmds[0]);
	if (shell->cmds && shell->cmds[0] && isbuiltin_p(shell->cmds) == 1)
	{
		err = builtin_p(shell->cmds, shell->lib);
		exit(err);
	}
	else
	{
		if (shell->cmds && shell->cmds[0] && \
		ft_strchr(shell->cmds[0], '/') != NULL)
			is_exe_file(shell->cmds);
		child(shell, current_token, loc_pipe);
	}
}

void	closepipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i <= shell->n_pipe)
	{
		if (isatty(shell->pipe[i][0]) == 1)
			close(shell->pipe[1][0]);
		if (isatty(shell->pipe[i][1]) == 1)
			close(shell->pipe[1][0]);
		free(shell->pipe[i]);
		i++;
	}
	free(shell->pipe);
}

void	child_execute(t_shell *shell, t_token *current_token, \
int pipe_loc, pid_t last_child)
{
	int		wrong_redir;

	dup2(STDOUT, STDOUT_FILENO);
	dup2(STDIN, STDIN_FILENO);
	shell->heredoc_on = 0;
	shell->delimiter = NULL;
	wrong_redir = get_redirs(shell, current_token);
	current_token = rm_redirect(current_token);
	if (current_token && current_token->prev == NULL)
		shell->tokens = current_token;
	expand_till_pipe(shell, current_token);
	fork_protected(shell);
	if (shell->child == 0)
	{
		if (wrong_redir == 1)
			exit(1);
		execute(shell, current_token, pipe_loc);
	}
	else
		parent_process_loop(shell, current_token, pipe_loc, last_child);
}

char	**duplist(t_list *list)
{
	char	**duplist;
	t_list	*listbuff;
	int		i;

	if (!list || !list->content)
		return (NULL);
	listbuff = list;
	duplist = malloc(sizeof(char *) * (ft_lstsize(listbuff) + 1));
	listbuff = list;
	i = 0;
	while (listbuff)
	{
		duplist[i] = (char *)((t_var *)((t_list *)listbuff)->content)->name;
		duplist[i] = ft_strjoin(duplist[i], "=");
		duplist[i] = join_free(duplist[i], \
		(char *)((t_var *)((t_list *)listbuff)->content)->data);
		listbuff = listbuff->next;
		i++;
	}
	duplist[i] = NULL;
	return (duplist);
}
