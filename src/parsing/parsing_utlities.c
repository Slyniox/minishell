/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utlities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:49:00 by balt              #+#    #+#             */
/*   Updated: 2024/02/28 17:07:47 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_pipes(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[0] == '|')
		return (1);
	while (line[i + 1])
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	has_double_pipes(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		i += skip_quotes(line, i);
		if (!line[i])
			return (0);
		if (line[i] == '|')
		{
			i++;
			while (is_space(line[i]) && line[i])
				i++;
			if (!line[i])
				return (0);
			if (line[i] == '|')
				return (i);
		}
		else
			i++;
	}
	return (0);
}

char	*rmv_double_pipes(char *line)
{
	int	i;

	if (!line)
		return (NULL);
	i = has_double_pipes(line);
	while (i > 0)
	{
		line = rmv_char(line, i);
		i = has_double_pipes(line);
	}
	return (line);
}

char	*after_redir(char *line, int pos, char *to_skip)
{
	int		i;
	char	*res;

	i = 0;
	pos++;
	if (line[pos] == '>' || line[pos] == '<')
		pos++;
	while (is_space(line[pos]) && line[pos])
		pos++;
	while (to_skip && to_skip[i])
	{
		i++;
		pos++;
	}
	i = 0;
	while (is_space(line[pos]) && line[pos])
		pos++;
	while (!is_token_nc(line, pos + i, 0) && line[i])
		i += (skip_quotes(line, pos + i) + 1);
	res = (char *) malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res = ft_fill(line, res, pos, i + pos);
	return (res);
}

char	*before_redir(char *line, int pos, char *value)
{
	int		i;
	int		j;
	char	*res;

	j = 0;
	i = 0;
	while (is_space(line[i]) && line[i])
		i++;
	if (i == pos)
		return (after_redir(line, pos, value));
	res = (char *) malloc(((pos - i) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < pos && line[i])
	{
		res[j] = line[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
