/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_export_print2.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:37 by lizhang       #+#    #+#                 */
/*   Updated: 2023/01/16 18:13:36 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
检查envars是否已经sort
用于print_export()
*/
int	sortedstr(char **envars)
{
	int	i;

	i = 0;
	while (envars[i] && envars[i + 1])
	{
		if (ft_strncmp(envars[i], envars[i + 1], ft_strlen(envars[i])) > 0)
			return (0);
		i++;
	}
	return (1);
}

/*
sort。用于print_export()
*/
void	sort_str(char **vars)
{
	int		i;
	char	*strbuf;

	i = 0;
	while (vars[i] && vars[i + 1])
	{
		if (ft_strncmp(vars[i], vars[i + 1], ft_strlen(vars[i])) > 0)
		{
			strbuf = vars[i];
			vars[i] = vars[i + 1];
			vars[i + 1] = strbuf;
		}
		i++;
	}
	i = 0;
}
