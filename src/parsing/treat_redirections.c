/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:51:19 by balt              #+#    #+#             */
/*   Updated: 2024/03/14 16:16:11 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_redirections(t_minishell *minishell, char *line, int arg)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\"')
			while (line[++i] != '\"' && line[i])
				;
		if (line[i] == '\'')
			while (line[++i] != '\'' && line[i])
				;
		if (!line[i])
			return (line);
		if ((line[i] == '>' && arg == 0) || (line[i] == '<' && (arg == 0  || line[i + 1] == '<')))
		{
			line = treat_redirect(minishell, line, i);
			if (line)
				line = rmv_alone_quotes(line);
			i = 0;
		}
		if (line && line[i])
			i++;
	}
	return (line);
}

char	*treat_redirect(t_minishell *minishell, char *line, int pos)
{
	int		redir_input;
	char	*br;
	char	*value;

	br = NULL;
	redir_input = 0;
	if (!line[pos + 1])
		return (free(line), NULL);
	if (line[pos + 1] == line[pos])
		redir_input = 1;
	if (is_token_nc(line, pos + redir_input, 0))
		return (free(line), NULL);
	value = get_redir_value(line, pos + redir_input);
	if (!value)
		return (free(line), NULL);
	br = before_redir(line, pos, value);
	minishell->ret = exec_redirect(minishell, rmv_alone_quotes(value),
			br, sign_id(line, pos, redir_input));
	if (minishell->ret == -1)
		return (free(br), free(value), free(line), NULL);
	if (sign_id(line, pos, redir_input) == HEREDOC)
		line = cut_heredoc(line, pos, rmv_alone_quotes(value));
	line = rmv_useless(trimline(line, update_pos(line), redir_input));
	line = rmv_double_pipes(line);
	return (free(br), free(value), line);
}

char	*get_redir_value(char *line, int pos)
{
	int		i;
	int		j;
	char	*res;

	j = 0;
	i = 0;
	if (line[pos] == '>' || line[pos] == '<')
		pos++;
	while (is_space(line[pos]) && line[pos])
		pos++;
	i += skip_quotes(line, pos + i);
	while (!is_token_nc(line, pos + i, 1) && !is_space(line[pos + i]))
		i++;
	res = (char *) malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (j < i)
	{
		res[j] = line[pos + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

int	is_token_nc(char *line, int pos, int arg)
{
	int	i;

	i = 0;
	if ((line[pos] == '>' || line[pos] == '<') && arg == 0)
		i++;
	while (line[pos + i] && is_space(line[pos + i]))
		i++;
	if (!line[pos + i])
		return (1);
	if (arg == 1 && (line[pos + i] == '\"' || line[pos + i] == '\''))
		return (1);
	if (line[pos + i] == '|' || line[pos + i] == '>' || line[pos + i] == '<')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == '\0')
		return (1);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}
