/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/26 14:37:58 by lizhang       #+#    #+#                 */
/*   Updated: 2023/01/31 20:37:38 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	sig_end(int signum)
{
	if (signum == SIGINT)
		exit(130);
	else if (signum == SIGTERM)
		exit(131);
}

void	heredoc(t_shell *shell)
{
	char	*buf;
	int		i;

	signal(SIGINT, &sig_end);
	signal(SIGTERM, &sig_end);
	i = 0;
	shell->heredoc_on = 1;
	if (shell->f_in != STDIN_FILENO)
		close(shell->f_in);
	dup2(0, STDIN_FILENO);
	shell->heredoc = ft_strdup("");
	buf = readline(">");
	while (buf && ft_strncmp(buf, shell->delimiter, \
	ft_strlen(shell->delimiter) + 1) != 0)
	{
		buf = ft_strjoin(buf, "\n");
		shell->heredoc = ft_strjoin(shell->heredoc, buf);
		buf = readline(">");
		i++;
	}
	shell->heredoc_on = 0;
	signal(SIGINT, &standard_sig_handler);
	signal(SIGTERM, &standard_sig_handler);
}

void	write_heredoc(t_shell *shell)
{
	int		heredocfd[2];

	pipe (heredocfd);
	heredoc(shell);
	if (shell->heredoc)
		write(heredocfd[1], shell->heredoc, ft_strlen(shell->heredoc));
	close(heredocfd[1]);
	dup2(heredocfd[0], STDIN_FILENO);
}
