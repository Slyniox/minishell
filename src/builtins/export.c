/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:38:38 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/19 12:54:24 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	length_before_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i - 1);
}

static int	replace_var(t_minishell *minishell, char **var, char *arg)
{
	if (*var)
		free(*var);
	*var = ft_strdup(arg);
	if (!(*var))
		return (get_error(minishell, NULL));
	return (0);
}

static int	check(t_minishell *minishell, char *arg)
{
	int		i;
	char	*var_name;

	if (!arg[0])
		return (ft_env(minishell), -1);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	var_name = (char *)malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (get_error(minishell, NULL));
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		var_name[i] = arg[i];
		i++;
	}
	var_name[i] = '\0';
	if (i >= 1 && arg[i] == '=' && arg[i - 1] == ' ')
		return(free(var_name), -1);
	if (!arg[i] || arg[0] == '=' || arg[ft_strlen(arg) - 2] == '=')
		return (free(var_name), -1);
	i = -1;
	while (minishell->env[++i])
		if (!ft_strncmp(minishell->env[i], var_name, length_before_equal(arg)))
			return (replace_var(minishell, &minishell->env[i], arg), free(var_name), -1);
	return (free(var_name), 0);
}

static char	*ft_strdup_without_n(char *src)
{
	int		i;
	char	*str;

	str = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != ' ' && src[i] != '\n')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_export(t_minishell *minishell, char *arg)
{
	int		i;
	char	**new_env;

	if (check(minishell, arg) == -1)
		return (0);
	i = -1;
	new_env = (char **)malloc(sizeof(char *)
			* (ft_tabsize(minishell->env) + 2));
	if (!new_env)
		return (get_error(minishell, NULL));
	while (minishell->env[++i])
	{
		new_env[i] = ft_strdup(minishell->env[i]);
		if (!new_env[i])
			return (get_error(minishell, NULL));
	}
	new_env[i] = ft_strdup_without_n(arg);
	if (!new_env[i])
		return (get_error(minishell, NULL));
	new_env[i + 1] = NULL;
	ft_freetab(minishell->env);
	minishell->env = ft_tabdup(new_env);
	if (!minishell->env)
		return (get_error(minishell, NULL));
	return (ft_freetab(new_env), 0);
}
