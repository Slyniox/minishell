/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:24:56 by balt              #+#    #+#             */
/*   Updated: 2024/03/20 00:05:42 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *err_mess)
{
	ft_putstr_fd(err_mess, 2);
	return ;
}

void	action(int signum)
{
	if (g_exit == 3)
		return ;
	if (signum == SIGINT)
	{
		g_exit = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	return ;
}
