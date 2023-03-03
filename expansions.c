/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 16:05:01 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/03 16:51:35 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	finddollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
			i = i + 2;
		else if (str[i] == '$' && str[i + 1] != 0)
			return (i + 1);
		else
			i++;
	}
	return (0);
}

/*
$? 用于检查error code，
*/
t_var	*findvar(char *name, t_lib *lib)
{
	t_list	*envarbuf;
	t_list	*ovarbuf;

	envarbuf = lib->envars;
	ovarbuf = lib->ovars;
	if (!name)
		return (NULL);
	while (envarbuf && lib->envars->content)
	{
		if (ft_strncmp(name, (char *)((t_var *)(envarbuf->content))->name, \
		ft_strlen(name) + 1) == 0)
			return (envarbuf->content);
		envarbuf = envarbuf->next;
	}
	while (ovarbuf && lib->ovars->content)
	{
		if (ft_strncmp((char *) \
		((t_var *)ovarbuf->content)->name, name, ft_strlen(name) + 1) == 0)
			return ((t_var *)ovarbuf->content);
		ovarbuf = ovarbuf->next;
	}
	return (NULL);
}
