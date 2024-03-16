/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:38:25 by balt              #+#    #+#             */
/*   Updated: 2024/03/14 01:42:40 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_q(char *line, int pos)
{
	int	i;

	i = 0;
	if (line[i + pos] == '\"')
		while (line[++i + pos] != '\"' && line[i + pos])
			;
	if (line[i + pos] == '\'')
		while (line[++i + pos] != '\'' && line[i + pos])
			;
	return (i);
}

int	ft_countwords(char *line, char c)
{
	int	i;
	int	cw;

	cw = 0;
	i = 0;
	while (line[i])
	{
		i += skip_q(line, i);
		if (line[i] == '\"' || line[i] == '\'')
			i++;
		while (line[i] != c && line[i] && line[i] != '\"' && line[i] != '\'')
			i++;
		if (line[i] != '\"' && line[i] != '\'')
			cw++;
		while (line[i] == c)
			i++;
	}
	return (cw);
}

char	**ft_free(char **tab, int i)
{
	int	p;

	p = 0;
	while (p < i)
	{
		free(tab[p]);
		p++;
	}
	free(tab);
	return (NULL);
}

int	skip_word(char	*line, char c, int i)
{
	if (line[i] == '\"' || line[i] == '\'')
		i++;
	while (line[i] != c && line[i] && line[i] != '\"' && line[i] != '\'')
		i++;
	return (i);
}

char	**ft_split_quotes(char *line, char c)
{
	int		j;
	int		i;
	char	**tab;

	i = 0;
	j = 0;
	tab = (char **) malloc((ft_countwords(line, c) + 1) * sizeof(char *));
	if (!tab)
		return (free(line), NULL);
	while (line[i])
	{
		i += skip_q(line, i);
		i = skip_word(line, c, i);
		if (line[i] != '\"' && line[i] != '\'')
		{
			tab[j] = ft_filltab(line, c, i);
			if (!tab[j])
				return (free(line), ft_free(tab, j));
			j++;
		}
		while (line[i] == c)
			i++;
	}
	tab[j] = 0;
	return (free_useless(tab));
}
