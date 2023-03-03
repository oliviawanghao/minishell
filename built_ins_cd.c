/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_cd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/13 16:10:08 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/13 14:59:36 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	cd_error(char *name, int number)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	ft_putstr_fd(name, STDERR);
	ft_putstr_fd(": ", STDERR);
	if (access(name, F_OK) >= 0 && opendir(name) == NULL)
	{
		ft_putendl_fd("Not a directory", STDERR);
		return (1);
	}
	ft_putstr_fd(strerror(number), STDERR);
	ft_putstr_fd("\n", STDERR);
	return (1);
}

int	cwd_error(void)
{
	perror("cd: error retrieving current directory: getcwd: \
cannot access parent directories: ");
	return (0);
}

int	add_oldpwd(char *cwd, t_lib *lib)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", cwd);
	varedit(oldpwd, lib);
	free(oldpwd);
	return (0);
}

char	*join_free(char *str1, char *str2)
{
	char	*buf;

	if (!str1 || !str2)
		return (NULL);
	buf = ft_strjoin(str1, str2);
	if (!buf)
		mallocerr();
	free(str1);
	return (buf);
}

int	cd_p(char **cmd, t_lib *lib)
{
	char	cwd[1000];
	char	*path;

	errno = 0;
	getcwd(cwd, 1000);
	if (!cmd[1])
		return (cd_nothing(lib));
	if (ft_strcmp(cmd[1], ".") != 0 && ft_strcmp(cmd[1], "..") != 0)
	{
		if (chdir(cmd[1]) >= 0)
			return (add_oldpwd(cwd, lib));
	}
	if (ft_strncmp(cmd[1], "-", 2) == 0)
		return (cd_dash());
	if (getcwd(cwd, 1000) == NULL || ft_strlen(cwd) == 0)
		return (cwd_error());
	path = ft_strjoin(cwd, "/");
	path = join_free(path, cmd[1]);
	if (chdir(path) < 0)
	{
		free(path);
		return (cd_error(cmd[1], errno));
	}
	free(path);
	return (add_oldpwd(cwd, lib));
}
