/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_export_var.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:02:40 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/19 16:18:41 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int	export_error(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (-1);
		else if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (i);
		i++;
	}
	return (-1);
}

t_var	*findvar_in_list(char *name, t_list *list)
{
	t_list	*buf;

	if (!list || !list->content || !name)
		return (NULL);
	buf = list;
	while (buf && buf->content)
	{
		if (ft_strcmp(((t_var *)buf->content)->name, name) == 0)
		{
			return ((t_var *)buf->content);
		}
		buf = buf->next;
	}
	return (NULL);
}

static int	export_e_message(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	return (1);
}

int	export_function(char *cmd, t_lib *lib)
{
	t_var	*var;
	char	**name;

	if (export_error(cmd) >= 0)
		return (export_e_message(cmd));
	name = ft_split(cmd, '=');
	var = findvar_in_list(name[0], lib->envars);
	if (!var && isvariable(cmd) == 0)
	{
		if (!findvar_in_list(name[0], lib->name_only))
			lib->name_only = addvar(lib->name_only, name[0]);
	}
	else if (var && isvariable(cmd) == 0)
		return (0);
	else if (var && isvariable(cmd) == 1 && name[1])
		var->data = substitute(var->data, name[1]);
	else if (!var && isvariable(cmd) == 1)
	{
		lib->envars = addvar(lib->envars, cmd);
		lib->name_only = rm_from_list(name[0], lib->name_only);
	}
	cleardarray(name);
	return (0);
}

int	export_p(char **cmd, t_lib *lib)
{
	int	check;
	int	err;
	int	i;

	i = 1;
	while (cmd[i])
	{
		check = export_function(cmd[i], lib);
		if (check != 0)
			err = check;
		i++;
	}
	return (err);
}
