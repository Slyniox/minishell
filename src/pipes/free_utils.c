/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:09:47 by balthazar         #+#    #+#             */
/*   Updated: 2024/03/14 02:18:00 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_big_tab(char ***tab)
{
	int	i;
	
	i = 0;
	while (tab[i])
	{
		ft_freetab(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	*free_cmds_tab(char ***tab, char **to_add, int tab_size, int add_size)
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
	return (NULL);
}
