/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 06:53:11 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/15 04:33:03 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_history(t_minishell *minishell)
{
	int			i;
	t_history	*tmp;

	i = 1;
	tmp = minishell->history;
	while (tmp)
	{
		if (tmp->cmd)
			ft_printf("[%d] - %s\n", i, tmp->cmd);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		i++;
	}
	return (0);
}
