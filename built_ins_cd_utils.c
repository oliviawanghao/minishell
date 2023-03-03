/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_cd_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:54:27 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/15 18:28:02 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	cd_dash(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR);
		return (1);
	}
	printf("%s\n", oldpwd);
	return (0);
}

int	cd_nothing(t_lib *lib)
{
	t_var	*home_var;
	char	*homepath;

	home_var = (t_var *)findvar("HOME", lib);
	if (home_var)
		homepath = home_var->data;
	if (!home_var || ft_strlen(homepath) == 0)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
		return (1);
	}
	chdir(getenv("HOME"));
	return (0);
}
