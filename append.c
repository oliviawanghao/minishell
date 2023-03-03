/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:55:37 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/15 18:31:53 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	last_char_pipe(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]) == 1)
		i++;
	while (str[i] == '|')
		i++;
	while (is_space(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		return (0);
	i = ft_strlen(str);
	while (i > 1 && is_space(str[i - 1]) == 1)
		i--;
	if (str[i - 1] == '|')
		return (1);
	return (0);
}

char	*append(char *line)
{
	char	*append;
	int		std_cpy;

	std_cpy = dup(STDIN_FILENO);
	signal(SIGINT, &sig_input);
	while (line && (nquotes(line) % 2 == 1 || \
	last_char_pipe(line) == 1))
	{
		append = readline(">");
		if (append)
		{
			line = join_free(line, append);
			free(append);
		}
		else
			break ;
	}
	dup2(std_cpy, STDIN_FILENO);
	signal(SIGINT, &p_int_handler);
	return (line);
}
