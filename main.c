/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 14:49:49 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/19 16:08:45 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	nquotes(char *line)
{
	int		i;
	int		count;
	char	q;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i];
			break ;
		}
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == q)
			count++;
		i++;
	}
	return (count);
}

t_lib	*lib_init(char **env)
{
	t_lib	*lib;

	lib = (t_lib *)malloc(sizeof(t_lib));
	lib->envars = env_vars(env);
	lib->ovars = (t_list *)malloc(sizeof(t_list));
	lib->ovars->content = NULL;
	lib->ovars->next = NULL;
	lib->name_only = (t_list *)malloc(sizeof(t_list));
	lib->name_only->content = NULL;
	lib->name_only->next = NULL;
	lib->err = malloc(sizeof(int));
	lib->err[0] = 0;
	return (lib);
}

t_shell	*shell_init(char *line, t_lib *lib)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->tokens = lexer(line);
	if (!shell->tokens)
		mallocerr();
	if (shell->tokens->type == (unsigned int)(-1))
	{
		free(shell->tokens);
		free(shell);
		return (NULL);
	}
	shell->f_in = STDIN;
	shell->f_out = STDOUT;
	shell->lib = lib;
	shell->heredoc_on = 0;
	shell->delimiter = NULL;
	shell->heredoc = NULL;
	shell->cmds = NULL;
	shell->heredoc_on = 0;
	return (shell);
}

void	main_loop(t_lib *lib)
{
	t_shell	*shell;
	char	*line;

	while (1)
	{
		signal(SIGINT, &p_int_handler);
		signal(SIGQUIT, &p_quit_handler);
		line = readline("minishell$");
		exit_function(line);
		line = append(line);
		if (errno == 9)
			lib->err[0] = 1;
		if (line && *line)
			add_history(line);
		if (line && ft_strlen(line) > 0 && errno != 9)
		{
			shell = shell_init(line, lib);
			if (shell)
			{
				minishell(shell);
				clearshell(shell);
			}
		}
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_lib	*lib;

	ac = 0;
	av = NULL;
	lib = lib_init(env);
	shlvl_increment(lib);
	main_loop(lib);
	return (0);
}
