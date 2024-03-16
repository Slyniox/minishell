/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:45:17 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/05 16:54:08 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_dirs(char **env)
{
	int		i;
	char	**dirs;

	i = 0;
	while (env[i] && ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	if (i == ft_tabsize(env))
		return (NULL);
	dirs = ft_split(env[i] + 5, ':');
	if (!dirs)
		return (NULL);
	return (dirs);
}

char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	int		len;
	char	*path;
	char	**dirs;

	i = -1;
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	dirs = get_path_dirs(env);
	if (!dirs)
		return (NULL);
	while (dirs[++i])
	{
		len = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
		path = (char *)malloc(sizeof(char) * len);
		if (!path)
			return (ft_freetab(dirs), NULL);
		ft_strcpy(path, dirs[i]);
		ft_strcat(path, "/");
		ft_strcat(path, cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_freetab(dirs), path);
		free(path);
	}
	return (ft_freetab(dirs), NULL);
}
