/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balt <balt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 03:02:58 by balt              #+#    #+#             */
/*   Updated: 2024/02/18 04:09:24 by balt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim2(char *line, int pos, int rv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (rv == 1)
		i++;
	if (!line[pos])
		return (line);
	while (is_space(line[pos + i]) && line[pos + i])
		i++;
	i += skip_quotes(line, pos + i);
	while (!is_token_nc(line, pos + i, 1) && line[pos + i])
		i++;
	while (j < i)
	{
		line = rmv_char(line, pos);
		j++;
	}
	while (is_space(line[0]) && line[0])
		line = rmv_char(line, 0);
	return (line);
}

int	update_pos(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i])
	{
		if (line[i] == '>' || line [i] == '<')
			return (i);
		i++;
	}
	return (0);
}

int	after_redir_index(char *line, int pos, char *to_skip)
{
	int		i;

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
	return (pos);
}

int	before_redir_index(char *line, int pos, char *value)
{
	int		i;

	i = 0;
	while (is_space(line[i]) && line[i])
		i++;
	if (i == pos)
		return (after_redir_index(line, pos, value));
	return (i);
}

char	*cut_heredoc(char *line, int pos, char *value)
{
	int	i;

	i = before_redir_index(line, pos, value);
	line = trim2(line, i, 0);
	return (line);
}
