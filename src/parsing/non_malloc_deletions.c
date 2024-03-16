/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_malloc_deletions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balt <balt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:42:57 by balt              #+#    #+#             */
/*   Updated: 2024/02/14 19:57:46 by balt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rmv_char(char *line, int pos)
{
	int		i;

	i = 0;
	while (line[i + pos] && line[i + pos + 1])
	{
		line[i + pos] = line[i + pos + 1];
		i++;
	}
	line[i + pos] = '\0';
	return (line);
}

char	*rmv_first_char(char *line, char to_rmv, int size)
{
	while (size >= 0)
	{
		if (line[size] == to_rmv)
		{
			line = rmv_char(line, size);
			break ;
		}
		size --;
	}
	return (line);
}

char	*rmv_alone_quotes(char *line)
{
	int	i;
	int	singles;
	int	doubles;

	i = 0;
	singles = 0;
	doubles = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			singles++;
		else if (line[i] == '\"')
			doubles++;
		i += smart_skipper(line, i, singles, doubles);
	}
	if (singles % 2 != 0)
		line = rmv_first_char(line, '\'', i);
	if (doubles % 2 != 0)
		line = rmv_first_char(line, '\"', i);
	return (line);
}

char	*trimline(char *line, int pos, int rv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (rv == 1)
		i++;
	while (is_space(line[pos + i]) && line[pos + i])
		i++;
	i += skip_quotes(line, pos + i);
	while (!is_token_nc(line, pos + i, 1) && !is_space(line[pos + i]))
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

char	*rmv_double_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		while (is_space(line[i]) && line[i + 1] && is_space(line[i + 1]))
			line = rmv_char(line, i + 1);
		i++;
	}
	return (line);
}
