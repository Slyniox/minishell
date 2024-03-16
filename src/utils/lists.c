/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:10:32 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/08 10:39:48 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstadd_back(t_history **lst, t_history *new)
{
	t_history	*tmp;

	if (!lst || !new)
	{
		if (!lst)
			ft_printf("Argument lst is NULL in lstadd_back() function.\n");
		if (!new)
			ft_printf("Argument new is NULL in lstadd_back() function.\n");
		return ;
	}
	tmp = lstlast(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}

void	lstclear(t_history **lst, void (*del)(void *))
{
	t_history	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			lstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}

void	lstdelone(t_history *lst, void (*del)(void *))
{
	if (!lst || !del)
	{
		if (!lst)
			ft_printf("Argument lst is NULL in lstdelone() function.\n");
		if (!del)
			ft_printf("Argument function del is NULL in lstdelone().\n");
		return ;
	}
	del(lst->cmd);
	free(lst);
}

t_history	*lstlast(t_history *lst)
{
	t_history	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_history	*lstnew(char *cmd)
{
	t_history	*list;

	list = (t_history *)malloc(sizeof(t_history));
	if (!list)
	{
		ft_printf("Argument lst is NULL in lstnew() function.\n");
		return (NULL);
	}
	list->cmd = ft_strdup(cmd);
	list->next = NULL;
	return (list);
}
