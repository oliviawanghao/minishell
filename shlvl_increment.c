/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shlvl_increment.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/15 17:48:08 by lizhang       #+#    #+#                 */
/*   Updated: 2023/01/31 19:02:29 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	shlvl_increment(t_lib *lib)
{
	t_var	*shlvl;
	char	*buf;
	int		lvl;

	shlvl = findvar("SHLVL", lib);
	if (shlvl && shlvl->data)
	{
		buf = shlvl->data;
		lvl = ft_atoi(shlvl->data);
		lvl++;
		shlvl->data = ft_itoa(lvl);
		free(buf);
	}
}
