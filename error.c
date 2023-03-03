/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 22:30:33 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/06 19:22:14 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
打印error。
*/
void	printerr(char *filename)
{
	char	*sh;
	char	*errmessage;

	errmessage = ft_strdup(filename);
	sh = ft_strjoin("minishell: ", errmessage);
	errmessage = ft_strjoin(sh, ": ");
	free(sh);
	sh = ft_strjoin(errmessage, strerror(errno));
	errmessage = ft_strjoin(sh, "\n");
	write(STDERR_FILENO, errmessage, ft_strlen(errmessage));
	if (errno == 2)
		exit(127);
	free(sh);
	exit(errno);
}

void	cmdnotfound(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(filename, STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
	errno = 127;
	exit(errno);
}

void	mallocerr(void)
{
	perror("");
	exit(EXIT_FAILURE);
}

void	multiple_shell(char *str)
{
	if (str && ft_strncmp("minishell", str, 10) == 0)
		str = ft_strjoin("./", str);
	if (str && ft_strncmp("./minishell", str, 12) == 0)
	{
		signal(SIGINT, &c_signal_reset);
		signal(SIGQUIT, &c_signal_reset);
	}
}
