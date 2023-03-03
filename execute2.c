/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 18:31:31 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/06 20:43:35 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	isbuiltin_c(char **cmd)
{
	if (ft_strncmp(cmd[0], "env", 4) == 0 || ft_strncmp(cmd[0], "echo", 5) == 0 \
	|| (ft_strncmp(cmd[0], "export", 7) == 0 && !cmd[1]) \
	|| ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (1);
	return (0);
}

int	isbuiltin_p(char **cmd)
{
	if (isvariable(cmd[0]) == 1)
		return (1);
	if (ft_strncmp(cmd[0], "cd", 3) == 0 || ft_strncmp(cmd[0], "exit", 5) == 0 \
	|| ft_strncmp(cmd[0], "unset", 6) == 0 || \
	(ft_strncmp(cmd[0], "export", 7) == 0 && cmd[1]))
		return (1);
	return (0);
}

char	*pathjoin(char *path, char *com)
{
	char	*path2;

	path = ft_strjoin(path, "/");
	path2 = ft_strjoin(path, com);
	free(path);
	return (path2);
}

char	**findfolder(char **env)
{
	int		dif;
	int		i;
	char	**folders;

	dif = 1;
	i = 0;
	while (dif != 0)
	{
		if (!env[i])
			return (NULL);
		dif = ft_strncmp("PATH=", env[i], 5);
		i++;
	}
	folders = ft_split(env[i - 1] + 5, ':');
	if (!folders)
		mallocerr();
	return (folders);
}

void	exe(char **env, char **cmds)
{
	char	**folders;
	char	*command;
	int		i;

	i = 0;
	execve(cmds[0], cmds, env);
	folders = findfolder(env);
	if (folders)
	{
		while (folders[i])
		{
			command = pathjoin(folders[i], cmds[0]);
			execve(command, cmds, env);
			i++;
		}
		cleardarray(folders);
	}
	if (ft_strchr(cmds[0], '/') == NULL)
		cmdnotfound(cmds[0]);
	else
		printerr(cmds[0]);
	exit(errno);
}
