/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/15 16:26:44 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/13 18:54:50 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	dir_error(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(filename, STDERR);
	ft_putendl_fd(": is a directory", STDERR);
	exit(126);
}

void	accesserror(char *filename)
{
	ft_putstr_fd(ft_strjoin("minishell: ", filename), STDERR);
	ft_putendl_fd(": Permission denied", STDERR);
	exit(126);
}

void	is_exe_file(char **cmds)
{
	char	*filename;

	if (!cmds || !cmds[0])
		return ;
	if (ft_strlen(cmds[0]) >= 2)
	{
		if (ft_strncmp(cmds[0], "./", 2) == 0)
			filename = ft_substr(cmds[0], 2, ft_strlen(cmds[0]) - 2);
		else
			filename = ft_strdup(cmds[0]);
		if (access(filename, F_OK) < 0)
		{
			perror(ft_strjoin("minishell: ", cmds[0]));
			exit(127);
		}
		else if (access(filename, X_OK) < 0)
			accesserror(filename);
		else if (opendir(filename) != NULL)
			dir_error(filename);
		free(filename);
	}
}

void	test_exe(char *cmds)
{
	multiple_shell(cmds);
	if (ft_strchr(cmds, '/') != NULL && opendir(cmds) != NULL)
		dir_error(cmds);
}
