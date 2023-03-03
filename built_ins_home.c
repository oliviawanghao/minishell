/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_home.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/13 14:27:55 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/15 17:52:21 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	expand_home(t_token *tokens)
{
	char	*homepath;
	t_token	*current_token;
	char	*buf;

	homepath = getenv("HOME");
	current_token = tokens;
	while (current_token && current_token->type != PIPE)
	{
		if (ft_strncmp(current_token->value, "~", 2) == 0)
		{
			free(current_token->value);
			current_token->value = ft_strdup(homepath);
		}
		else if (ft_strncmp(current_token->value, "~/", 2) == 0)
		{
			buf = current_token->value;
			current_token->value = \
			ft_strjoin(homepath, buf + 1);
			free(buf);
		}
		current_token = current_token->next;
	}
}
