/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:47:39 by balt              #+#    #+#             */
/*   Updated: 2024/03/18 15:30:07 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*surplus(char *line, int pos, char *val_name)
{
	int		i;
	int		j;
	int		parc;
	char	*res;

	parc = 0;
	i = 0;
	j = 0;
	while (val_name[i])
		i++;
	while (line[j + i + pos])
		j++;
	res = (char *) malloc((j + 1) * sizeof(char));
	if (!res)
		return (free(line), free(val_name), NULL);
	while (line[pos + i] && j > 1)
	{
		res[parc] = line[pos + i];
		i++;
		parc++;
	}
	res[parc] = '\0';
	return (free(val_name), res);
}

char	*add_val(char *line, int pos, char *val)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	i = 0;
	while (val && val[i])
		i++;
	temp = (char *) malloc((pos + i + 1) * sizeof(char));
	if (!temp)
		return (free(line), NULL);
	i = 0;
	while (i < pos)
	{
		temp[i] = line[i];
		i++;
	}
	while (val && val[j])
	{
		temp[i + j] = val[j];
		j++;
	}
	temp[i + j] = '\0';
	return (free(line), temp);
}

char	*insert_val(t_minishell *minishell, char *line, int pos, char *val_name)
{
	char	*insert;
	char	*temp;
	int		i;

	i = 0;
	insert = get_env(minishell, val_name);
	if (!insert)
		return (rmv_val(minishell, pos, val_name));
	temp = surplus(line, pos, val_name);
	if (!temp)
		return (free(line), free(insert), NULL);
	line = add_val(line, pos, insert);
	if (!line)
		return (free(insert), free(temp), NULL);
	while (line[i])
		i++;
	line = add_val(line, i, temp);
	if (!line)
		return (free(insert), free(temp), NULL);
	return (free(insert), free(temp), line);
}

char	*line_add_val(t_minishell *minishell, char *line, int pos)
{
	char	*to_get;
	int		i;
	int		j;

	j = 0;
	to_get = NULL;
	i = 1;
	while (line[pos + i] && !is_sep(line[pos + i], i)
		&& line[pos + i -1] != '?')
		i++;
	if (i > 1 || line[pos + i] == '?')
		to_get = (char *)malloc((i + 1) * sizeof(char));
	if (!to_get)
	{
		line = insert_val(minishell, line, pos, NULL);
		return (line);
	}
	while (j < i && !is_sep(line[j + 1 + pos], 3) && line[pos + j] != '?')
	{
		to_get[j] = line[pos + j + 1];
		j++;
	}
	to_get[j] = '\0';
	line = insert_val(minishell, rmv_char(line, pos), pos, to_get);
	return (line);
}

char	*replace_vals(t_minishell *minishell, char *line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line)
			line = rmv_alone_quotes(line);
		if (line && line[i] == '\'' && !in_quotes(line, i))
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line && line[i] == '$' && !prev_heredoc(line, i))
			line = line_add_val(minishell, line, i);
		if (!line)
			return (NULL);
		if (line[i])
			i++;
	}
	return (line);
}
