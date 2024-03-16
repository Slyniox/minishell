/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:54:37 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/28 23:42:49 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_useless(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		if (is_empty(tab[i]))
		{
			free(tab[i]);
			tab[i] = 0;
		}
		i++;
	}
	return (tab);
}

char	*rmv_useless(char *line)
{
	if (!line)
		return (NULL);
	while ((is_space(line[0]) || line[0] == '|') && line[0])
		rmv_char(line, 0);
	return (line);
}

char	*rmv_pipeline(char *line)
{
	int	i;

	i = 0;
	line = rmv_useless(line);
	if (!line[i])
		return (NULL);
	while (line[i + 1])
		i++;
	while (i > 0 && (is_space(line[i]) || line[i] == '|'))
		i--;
	if (line[i] && !is_space(line[i]) && line[i] != '|')
		i++;
	while (line[i])
		line = rmv_char(line, i);
	return (line);
}

char	**rmv_pipes(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		tab[i] = rmv_pipeline(tab[i]);
		i++;
	}
	return (tab);
}

char	*rmv_val(t_minishell *minishell, int pos, char *val_name)
{
	int	i;

	i = 0;
	while (val_name && val_name[i])
		i++;
	while (i > 0)
	{
		minishell->line = rmv_char(minishell->line, pos);
		i--;
	}
	free(val_name);
	return (minishell->line);
}
