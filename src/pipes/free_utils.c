/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:09:47 by balthazar         #+#    #+#             */
/*   Updated: 2024/03/19 23:46:18 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_freetab_n(char **tab, int i)
{
	int	j;

	j = 0;
	while (tab[j] || j == i)
	{
		if (j == i && tab[j + 1])
			j++;
		else if (j == i && !tab[j + 1])
			break ;
		free(tab[j]);
		tab[j] = NULL;
		j++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

void	*free_big_tab(char ***tab)
{
	int	i;
	
	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		ft_freetab(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

void	*fbtn(char ***tab, int j, int i)
{
	int	e;

	e = 0;
	while (tab[e])
	{
		if (e != j)
			ft_freetab(tab[e]);
		else
			ft_freetab_n(tab[e], i);
		tab[e] = NULL;
		e++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

void	free_cmds_tab(char ***tab, char **to_add, int tab_size, int add_size)
{
	int	i;
	
	i = 0;
	while (i < add_size)
	{
		free(to_add[i]);
		i++;
	}
	free(to_add);
	i = 0;
	while (i < tab_size)
	{
		ft_freetab(tab[i]);
		i++;
	}
	free(tab);
}
