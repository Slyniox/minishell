/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:41:02 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/19 23:00:20 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_pwd(char *pwd)
{
	int	i;

	i = 0;
	if (!pwd)
		return (NULL);
	while (pwd && pwd[i] && i < 4)
	{
		pwd = rmv_char(pwd, 0);
		i++;
	}
	return (pwd);
}

static char	*get_home(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], "HOME=", 5) == 0)
			return (ft_strdup(minishell->env[i] + 5));
		i++;
	}
	return (NULL);
}

static char	*set_target(t_minishell *minishell)
{
	char	*target;

	target = NULL;
	if (ft_strncmp(minishell->line, "cd ~", 4) == 0
		|| (ft_strncmp(minishell->line, "cd", 2) == 0
			&& ft_strlen(minishell->line) == 2))
		target = get_home(minishell);
	else if (ft_strncmp(minishell->line, "..", 2) == 0)
		target = ft_strdup(minishell->line);
	else if (ft_strncmp(minishell->line, "cd", 2) == 0)
		target = ft_strdup(minishell->line + 3);
	else if (ft_strncmp(minishell->line, ".", 1) == 0)
		return (NULL);
	else
		target = ft_strdup(minishell->line);
	return (target);
}

int	ft_cd(t_minishell *minishell)
{
	int		i;
	char	*target;
	char	*pwd;
	char	*temp;

	target = set_target(minishell);
	if (!target)
		return (0);
	if (chdir(target) == -1)
		return (free(target), get_error(minishell, NULL));
	pwd = getcwd(NULL, 0);
	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], "PWD=", 4) == 0)
		{
			temp = ft_strjoin("OLDPWD=", trim_pwd(minishell->env[i]));
			if (!temp)
				return (free(pwd), free(target), 0);
			ft_export(minishell, temp);
			if (!minishell->env)
				return (free(temp), free(pwd), free(target), 0);
			(free(minishell->env[i]), free(minishell->path));
			minishell->env[i] = ft_strjoin("PWD=", pwd);
			minishell->path = ft_strdup(pwd);
			return (free(temp), free(pwd), free(target), 0);
		}
		i++;
	}
	return (free(pwd), free(target), 0);
}
