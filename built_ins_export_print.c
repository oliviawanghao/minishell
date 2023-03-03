/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_export_print.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 16:17:08 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/06 15:17:40 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

/*
在variable中创建了env的list
把env的list变成**char，用于print_export()
*/
static char	**duplist_with_quote(t_list *list)
{
	char	**duplist;
	t_list	*listbuff;
	int		i;

	if (!list || !list->content)
		return (NULL);
	listbuff = list;
	duplist = malloc(sizeof(char *) * (ft_lstsize(listbuff)+1));
	if (!duplist)
		mallocerr();
	listbuff = list;
	i = 0;
	while (listbuff)
	{
		duplist[i] = (char *)((t_var *)((t_list *)listbuff)->content)->name;
		duplist[i] = ft_strjoin(duplist[i], "=\"");
		duplist[i] = ft_strjoin(duplist[i], \
		(char *)((t_var *)((t_list *)listbuff)->content)->data);
		duplist[i] = ft_strjoin(duplist[i], "\"");
		listbuff = listbuff->next;
		i++;
	}
	duplist[i] = NULL;
	return (duplist);
}

char	**duplist_name_only(t_list *list)
{
	char	**duplist;
	t_list	*listbuff;
	int		i;

	if (!list || !list->content)
		return (NULL);
	listbuff = list;
	duplist = malloc(sizeof(char *) * (ft_lstsize(listbuff) + 1));
	listbuff = list;
	listbuff = list;
	i = 0;
	while (listbuff && listbuff->content)
	{
		duplist[i] = (char *)((t_var *)((t_list *)listbuff)->content)->name;
		listbuff = listbuff->next;
		i++;
	}
	duplist[i] = NULL;
	return (duplist);
}

/*
export，用于build_ins.c
*/

void	print_darray(char **dup)
{
	int	i;

	i = 0;
	while (dup[i])
	{
		printf("declare -x %s\n", dup[i]);
		i++;
	}
}

void	print_export(t_lib *lib)
{
	char	**dup;

	dup = duplist_with_quote(lib->envars);
	if (!dup)
		return ;
	while (sortedstr(dup) == 0)
		sort_str(dup);
	print_darray(dup);
	cleardarray(dup);
	dup = duplist_name_only(lib->name_only);
	if (!dup)
		return ;
	while (sortedstr(dup) == 0)
		sort_str(dup);
	print_darray(dup);
	cleardarray(dup);
}

/*
打印environment variable
和env_vars()同服。
*/
void	print_env(t_list *envars)
{
	t_list	*buff;

	buff = envars;
	while (buff)
	{
		printf("%s=%s\n", (char *)((t_var *)((t_list *)buff)->content)->name, \
		(char *)((t_var *)((t_list *)buff)->content)->data);
		buff = buff->next;
	}
}
