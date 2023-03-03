/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_utils.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:17:48 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/19 16:18:33 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <histedit.h>
# include "libft/libft.h"

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

typedef enum s_token_type
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXPANSION,
	LITERAL,
	GREAT,
	LESS,
	GREATGREAT,
	LESSLESS,
	PIPE,
	BACKSLASH,
	SPACE,
	UNKNOWN,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				len;
	int				space;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_var
{
	char	*name;
	char	*data;
}	t_var;

typedef struct s_lib
{
	t_list	*envars;
	t_list	*ovars;
	t_list	*name_only;
	int		*err;
}	t_lib;

typedef struct s_shell
{
	t_token	*tokens;
	int		n_pipe;
	char	**cmds;
	int		f_in;
	int		f_out;
	int		**pipe;
	pid_t	child;
	t_lib	*lib;
	int		heredoc_on;
	char	*delimiter;
	char	*heredoc;
}	t_shell;

//--init----------
t_shell	*shell_init(char *line, t_lib *lib);
t_lib	*lib_init(char **env);
void	pipe_prepare(t_shell *shell);
int		count_pipes(t_token *token);
t_token	*next_pipe(t_token *current_token);
void	main_loop(t_lib *lib);
void	minishell(t_shell *shell);
void	shlvl_increment(t_lib *lib);

//------------------------------------------------------------

int		nquotes(char *line);
void	multiple_shell(char *str);
char	*join_free(char *str1, char *str2);
char	*substitute(char *ptr1, char *ptr2);

//--signal-----------
void	p_int_handler(int signum);
void	p_quit_handler(int signum);
void	c_signal_reset(int signum);
void	sighandler(int signum);
void	standard_sig_handler(int signum);
void	sig_input(int signum);

//--lexer---------------
t_token	*lexer(char *input);
char	**token_to_cmd(t_token *tokens);

//--lexer utils---------------
void	get_value(t_token *current_token, char *input_value, int i);
int		is_symbol(char c);
int		is_space(char c);
int		is_quote(char c);
t_token	*add_new_token(t_token *current_token);
int		last_char_pipe(char *str);
char	*append(char *line);

//--var functions---------------
t_var	*splitvar(char *str);
t_list	*env_vars(char **env);
int		isvariable(char *str);
t_list	*addvar(t_list *list, char *str);
int		finddollar(char *str);
t_var	*findvar(char *name, t_lib *lib);
void	varedit(char *str, t_lib *lib);
void	echo_print(char **cmds);
char	*ft_itoa(int i);
t_list	*rm_from_list(char *name, t_list *list);

//--heredoc---------------
void	heredoc(t_shell *shell);
void	write_heredoc(t_shell *shell);
void	heredoc_without_cmd(t_shell *shell);

//--builtin functions---------------
int		builtin_c(char **cmd, t_lib *lib);
int		builtin_p(char **cmd, t_lib *lib);
int		isbuiltin_c(char **cmd);
int		isbuiltin_p(char **cmd);
int		sortedstr(char **envars);
void	sort_str(char **vars);
char	**duplist(t_list *list);
void	print_env(t_list *envars);
void	print_export(t_lib *lib);
void	list_free_item(t_list *list);
t_list	*unset_in_list(char *name, t_list *list);
int		unset_var(char **name, t_lib *lib);
void	var_sub(t_token *tokens, t_lib *lib);
void	expand_home(t_token *tokens);
void	expand_till_pipe(t_shell *shell, t_token *current_token);
void	exit_function(char *line);
int		cd_dash(void);
int		cd_nothing(t_lib *lib);
int		cd_error(char *name, int number);
int		add_oldpwd(char *cwd, t_lib *lib);
int		cd_p(char **cmd, t_lib *lib);
int		export_error(char *str);
t_var	*findvar_in_list(char *name, t_list *list);
t_list	*rm_from_list(char *name, t_list *list);
int		export_p(char **cmd, t_lib *lib);
int		exit_argument(char **cmds);

//--exe functions---------------
int		syntax_error(t_token *tokens);
int		is_redirect(int type);
int		get_redirs(t_shell *shell, t_token *tokens);
t_token	*rm_redirect(t_token *tokens);
void	child_execute(t_shell *shell, t_token *current_token, \
		int loc_pipe, pid_t last_child);
void	parent_process_loop(t_shell *shell, \
		t_token *current_token, int pipe_loc, pid_t last_child);
void	execute(t_shell *shell, t_token *current_token, int loc_pipe);
void	exe(char **env, char **cmds);
void	is_exe_file(char **cmds);
void	child(t_shell *shell, t_token *current_token, int pipe_loc);
void	dir_error(char *filename);
void	fork_protected(t_shell *shell);
void	test_exe(char *cmds);

//--pipex functions
int		parsecommand(char *com, char *condition);
void	printerr(char *filename);
char	*pathjoin(char *path, char *com);
char	**findfolder(char **env);
void	mallocerr(void);
void	cmdnotfound(char *filename);
void	printerr(char *filename);
void	rl_replace_line(const char *text, int clear_undo);

//--clear functions
void	cleardarray(char **array);
void	free_var_content(void *item);
void	closepipes(t_shell *shell);
void	clearshell(t_shell *shell);
void	free_one_token(t_token *token);
void	clearvarlist(t_list *lst);

#endif