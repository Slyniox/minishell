/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:29:06 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/29 04:29:03 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *args)
{
	int		i;
	bool	is_alpha;
	char	**splited_args;

	i = 0;
	splited_args = ft_split(args, ' ');
	if (!splited_args)
		return (-1);
	while (args[i])
	{
		if (ft_isalpha(args[i]) && !is_alpha)
			return (2);
		if (args[i] >= '0' && args[i] <= '9')
			is_alpha = true;
		i++;
	}
	if (ft_tabsize(splited_args) > 1)
		return (1);
	return (0);
}

int	ft_exit(t_minishell *minishell, char *args)
{
	int	ret;

	ret = parsing(args);
	minishell->exit = true;
	if (ret == 1)
	{
		ft_printf("minishell: exit: too many arguments\n");
		minishell->ret = 5;
		minishell->exit = false;
		return (minishell->ret);
	}
	else if (ret == 2)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", args);
		minishell->ret = 255;
		exit(255);
	}
	if (args)
		return (ft_atoi(args));
	return (0);
}
