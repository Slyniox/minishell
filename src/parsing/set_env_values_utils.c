/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_values_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:49:47 by balt              #+#    #+#             */
/*   Updated: 2024/02/29 04:22:00 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prev_heredoc(char *line, int pos)
{
	int	i;

	i = pos - 1;
	if (pos == 0)
		return (0);
	while (is_space(line[i]) && i > 0)
		i--;
	if (line[i] == '<')
	{
		if (i - 1 >= 0 && line[i - 1] == '<')
			return (1);
	}
	return (0);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

int	is_sep(char c, int pos)
{
	if (pos == 1 && c == '?')
		return (0);
	if (c == ' ' || (c >= '\t' && c <= '\r')
		|| c == '\'' || c == '\"' || c == '$')
		return (1);
	return (0);
}

int	check_for_path(char *line, int pos)
{
	if (line[pos] && line[pos + 1] && line[pos + 2] && line[pos + 3])
	{
		if (line[pos] == 'P' && line[pos + 1] == 'A'
			&& line[pos + 2] == 'T' && line[pos + 3] == 'H')
			return (1);
	}
	return (0);
}

char	*replace_path(t_minishell *minishell, char *line, int pos)
{
	char	*path;

	path = (char *) malloc(5 * sizeof(char));
	if (!path)
		return (free(line), NULL);
	path[0] = 'P';
	path[1] = 'A';
	path[2] = 'T';
	path[3] = 'H';
	path[4] = '\0';
	line = insert_val(minishell, line, pos, path);
	return (line);
}
