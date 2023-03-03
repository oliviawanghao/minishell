/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 18:07:48 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/11 17:11:32 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	exit_function(char *line)
{
	if (line == NULL)
	{
		write(1, "\e[1Aminishell$ exit\n", 21);
		exit(EXIT_SUCCESS);
	}
}

int	isalldigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	larger_than_ll(char *str)
{
	char	*max_ll;
	char	*str2;

	str2 = str;
	if (str2[0] == '-')
	{
		str2 = str2 + 1;
		max_ll = "9223372036854775808";
	}
	else
		max_ll = "9223372036854775807";
	if (ft_strlen(str2) > ft_strlen(max_ll))
		return (1);
	else if (ft_strlen(str2) == ft_strlen(max_ll))
		return (ft_strcmp(str2, max_ll));
	else
		return (0);
}

int	exit_argument(char **cmds)
{
	if (!cmds[1])
		exit(EXIT_SUCCESS);
	else if (cmds[1] && (isalldigit(cmds[1]) == 0 || \
	larger_than_ll(cmds[1]) > 0))
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmds[1], STDERR);
		ft_putstr_fd(" numeric argument required\n", STDERR);
		exit(255);
	}
	else if (cmds[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (1);
	}
	else
	{
		exit(ft_atoi(cmds[1]));
	}
	return (1);
}
