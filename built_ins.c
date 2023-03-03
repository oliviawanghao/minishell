/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 14:46:48 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/13 15:26:27 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"
/*
cd,exit,unset,export
如果export后面没有option，就在parent中。
用于execute
*/
int	builtin_p(char **cmd, t_lib *lib)
{
	if (isvariable(cmd[0]) == 1)
		varedit(cmd[0], lib);
	if (ft_strncmp("cd", cmd[0], 3) == 0)
		return (cd_p(cmd, lib));
	if (ft_strncmp("unset", cmd[0], 6) == 0)
		return (unset_var(cmd, lib));
	if (ft_strncmp("exit", cmd[0], 5) == 0)
		return (exit_argument(cmd));
	if (ft_strncmp("export", cmd[0], 7) == 0 && cmd[1] && cmd[1][0] != '#')
		return (export_p(cmd, lib));
	return (EXIT_SUCCESS);
}

/*
env,echo,export,pwd
有output，需要在child process
export没有option，需要打出所有的，就在child中。
用于execute
*/
int	builtin_c(char **cmd, t_lib *lib)
{
	char	pwd[1000];

	if (ft_strncmp("echo", cmd[0], 5) == 0)
	{
		echo_print(cmd);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp("export", cmd[0], 7) == 0)
	{
		print_export(lib);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp("pwd", cmd[0], 4) == 0)
	{
		if (!(getcwd(pwd, 1000)))
		{
			perror("");
			exit(errno);
		}
		printf("%s\n", pwd);
	}
	if (ft_strncmp("env", cmd[0], 4) == 0)
		print_env(lib->envars);
	exit(EXIT_SUCCESS);
}
