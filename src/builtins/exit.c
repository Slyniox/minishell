/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:29:06 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/19 16:22:19 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_minishell *minishell, char *args)
{
	int		i;
	char	**splited_args;

	i = 0;
	splited_args = ft_split(args, ' ');
	if (!splited_args)
		return (-1);
	if (ft_tabsize(splited_args) > 2)
		return (ft_freetab(splited_args), 1);
	if (!splited_args[1])
		return (ft_freetab(splited_args), 0);
	while (splited_args[1][i])
	{
		if (!ft_isdigit(splited_args[1][i]) && !is_space(splited_args[1][i]))
			return (ft_freetab(splited_args), 2);
		i++;
	}
	minishell->ret = ft_atoi(splited_args[1]);
	return (ft_freetab(splited_args), 0);
}

int	ft_exit(t_minishell *minishell, char *args)
{
	int	ret;

	minishell->ret = 255;
	ret = parsing(minishell, args);
	if (ret == 1)
	{
		ft_printf("minishell: exit: too many arguments\n");
		minishell->ret = 5;
		return (minishell->ret);
	}
	else if (ret == 2)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", args);
		minishell->ret = 255;
		(free_all(minishell), free_big_tab(minishell->cmds));
		exit(minishell->ret);
	}
	(free_all(minishell), free_big_tab(minishell->cmds));
	exit(minishell->ret);
}
