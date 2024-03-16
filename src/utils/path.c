/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:03:08 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/05 17:12:12 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_cd_shortcut(char *cmd)
{
	struct stat	path_stat;

	if ((ft_strncmp(cmd, "cd", 2) == 0 && !(*(cmd + 2)))
		|| (ft_strncmp(cmd, "cd", 2) == 0 && *(cmd + 2) == ' ')
		|| (ft_strncmp(cmd, "..", 2) == 0 && !(*(cmd + 2)))
		|| (ft_strncmp(cmd, ".", 1) == 0 && !(*(cmd + 2)))
		|| (ft_strncmp(cmd, "~", 1) == 0 && !(*(cmd + 2))))
		return (true);
	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

char	*get_env(t_minishell *minishell, char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (NULL);
	while (minishell->env[i])
	{
		if (ft_strncmp(value, "?", 1) == 0)
			return (ft_itoa(minishell->ret));
		if (ft_strncmp(minishell->env[i], value, ft_strlen(value)) == 0)
			return (minishell->env[i] + ft_strlen(value) + 1);
		i++;
	}
	return (NULL);
}
