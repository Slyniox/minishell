/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:38:11 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/05 16:46:05 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	length_before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i - 1);
}

static int	remake_env(t_minishell *minishell, int pos)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = 0;
	new_env = (char **)malloc(sizeof(char *) * ft_tabsize(minishell->env) + 1);
	if (!new_env)
		return (get_error(minishell, NULL));
	while (minishell->env[++i])
	{
		if (i != pos)
		{
			new_env[j] = ft_strdup(minishell->env[i]);
			if (!new_env[j])
				return (get_error(minishell, NULL));
			j++;
		}
	}
	new_env[j] = NULL;
	ft_freetab(minishell->env);
	minishell->env = ft_tabdup(new_env);
	if (!minishell->env)
		return (get_error(minishell, NULL));
	return (ft_freetab(new_env), 0);
}

int	ft_unset(t_minishell *minishell, char *arg)
{
	int	i;

	i = 0;
	if (!minishell->env)
		return (1);
	while (minishell->env[i])
	{
		if (!ft_strncmp(minishell->env[i], arg, length_before_equal(arg)))
			return (remake_env(minishell, i));
		i++;
	}
	return (0);
}
