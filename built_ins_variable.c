/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_variable.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 16:11:02 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/11 18:26:04 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
从=分开，变成name和data
用于addvar()
this only edits var data
*/
t_var	*splitvar(char *str)
{
	t_var	*var;
	int		len;

	if (!str)
		return (NULL);
	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		mallocerr();
	len = 0;
	while (str[len])
	{
		if (str[len] == '=')
			break ;
		len++;
	}
	var->name = ft_substr(str, 0, len);
	var->data = ft_substr(str, len + 1, ft_strlen(str) - len);
	return (var);
}

/*
添加一个var，包括自己新加的。
用于 env_vars(),
*/
t_list	*addvar(t_list *list, char *str)
{
	t_list	*var;

	if (!str)
		return (list);
	var = (t_list *)malloc(sizeof(t_list));
	if (!var)
		mallocerr();
	var->content = (void *)splitvar(str);
	var->next = NULL;
	if (!list)
		list = var;
	else if (list->content == NULL)
	{	
		list->content = var->content;
		free(var);
		list->next = NULL;
	}
	else
		ft_lstadd_back(&list, var);
	return (list);
}

/*
开始以后，存下所有env var
*/
t_list	*env_vars(char **env)
{
	t_list	*env_vars;
	t_list	*var;
	int		i;

	i = 0;
	while (env[i])
	{
		var = (t_list *)malloc(sizeof(t_list));
		var->content = (void *)splitvar(env[i]);
		var->next = NULL;
		if (i == 0)
			env_vars = var;
		else
			ft_lstadd_back(&env_vars, var);
		i++;
	}
	return (env_vars);
}

/*
检查有没有=，是否以数字开始，
如果以数字开始，就不是var。
*/
int	isvariable(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '=')
		return (0);
	if (ft_isalpha(str[0]) == 0)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '=')
			return (0);
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/*
替换var的data
*/
void	varedit(char *str, t_lib *lib)
{
	void	*var;
	t_var	*var_item;
	char	*buf;

	var_item = splitvar(str);
	var = findvar(var_item->name, lib);
	if (var)
	{
		buf = ((t_var *)var)->data;
		((t_var *)var)->data = ft_strdup((char *)(((t_var *)var_item)->data));
		free(buf);
	}
	else
		lib->ovars = addvar(lib->ovars, str);
	free_var_content(var_item);
}
