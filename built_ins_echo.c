/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_echo.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/27 16:51:42 by lizhang       #+#    #+#                 */
/*   Updated: 2023/01/15 17:41:04 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
edge case: -n and all -nnnnnnnnn
*/
int	only_n(char *str)
{
	int	i;

	if (!str || ft_strlen(str) == 0)
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[0] == '-' && i > 1 && str[i] == 0)
		return (1);
	return (0);
}

/*
edge case: -n and all -nnnnnnnnn
*/
int	echo_n(char **cmds)
{
	int	i;
	int	ind;

	i = 1;
	ind = 1;
	if (!cmds[1])
		return (ind);
	while (cmds[i] && (ft_strncmp(cmds[i], "-n", 3) == 0 || \
	only_n(cmds[i]) == 1))
	{
		ind = ind + 1;
		cmds[i][0] = 0;
		i++;
	}
	return (ind);
}

/*
real echo,
self written.
用于built_ins.c
*/
void	echo_print(char **cmds)
{
	int	nl;
	int	i;

	nl = 1;
	if (!cmds[1])
	{
		write(1, "\n", 2);
		return ;
	}
	i = echo_n(cmds);
	if (cmds[1] && i > 1)
		nl = 0;
	while (cmds[i])
	{
		printf("%s", cmds[i]);
		if (cmds[i + 1])
			printf(" ");
		i++;
	}
	if (nl == 1)
		printf("\n");
}
