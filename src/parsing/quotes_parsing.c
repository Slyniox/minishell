/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:45:54 by balt              #+#    #+#             */
/*   Updated: 2024/03/14 01:36:26 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	smart_skipper(char *line, int pos, int nb1, int nb2)
{
	int	i;

	i = 0;
	if ((line[pos] == '\'' && nb1 % 2 == 0)
		|| (line[pos] == '\"' && nb2 % 2 == 0))
		return (1);
	if (line[pos] == '\'')
	{
		i++;
		while (line[pos + i] && line[pos + i] != '\'')
			i++;
		if (line[pos + i])
			return (i);
		return (1);
	}
	if (line[pos] == '\"')
	{
		i++;
		while (line[pos + i] && line[pos + i] != '\"')
			i++;
		if (line[pos + i])
			return (i);
	}
	return (1);
}

int	in_quotes(char *line, int pos)
{
	int	i;
	int	in_quotes;

	in_quotes = 0;
	i = 0;
	while (line[i] && i < pos)
	{
		if (line[i] == '\"')
			in_quotes++;
		i++;
	}
	return (in_quotes % 2);
}

int	skip_quotes(char *line, int pos)
{
	int	res;

	res = 0;
	if (!line)
		return (0);
	if (line[pos] == '\"')
	{
		res++;
		while (line[pos + res] && line[pos + res] != '\"')
			res++;
		return (res);
	}
	if (line[pos] == '\'')
	{
		res++;
		while (line[pos + res] && line[pos + res] != '\'')
			res++;
		return (res);
	}
	return (res);
}

t_redirect_code	sign_id(char *line, int pos, int redir_input)
{
	if (!line || !line[pos])
		return (0);
	if (line[pos] == '<' && redir_input == 0)
		return (INPUT);
	if (line[pos] == '<' && redir_input == 1)
		return (HEREDOC);
	if (line[pos] == '>' && redir_input == 0)
		return (OUTPUT);
	if (line[pos] == '>' && redir_input == 1)
		return (APPEND);
	return (0);
}
