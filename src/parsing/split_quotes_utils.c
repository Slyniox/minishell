/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balt <balt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:22:01 by balt              #+#    #+#             */
/*   Updated: 2024/02/16 21:27:20 by balt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill(char *line, char *tab, int i, int pos)
{
	int	j;

	j = 0;
	while (i < pos)
	{
		tab[j] = line[i];
		j++;
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

char	*ft_filltab(char *line, char c, int pos)
{
	int		i;
	char	*res;

	i = pos;
	if (i > 0)
		i--;
	while (line[i] != c && i > 0)
	{
		if (line[i] == '\'')
			while (line[--i] != '\'')
				;
		if (line[i] == '\"')
			while (line[--i] != '\"')
				;
		if (i > 0)
			i--;
	}
	res = (char *) malloc(((pos - i) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res = ft_fill(line, res, i, pos);
	if (res[0] == c)
		rmv_char(res, 0);
	return (res);
}
