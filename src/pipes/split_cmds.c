/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:17:47 by balthazar         #+#    #+#             */
/*   Updated: 2024/03/17 17:14:27 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***tab_add(char ***tab, char **cmds, int pos, int ret)
{
	int		i;
	int		j;
	char	**to_add;

	j = 0;
	i = 0;
	while (tab[i])
		i++;
	to_add = (char **) malloc(((pos - ret) + 2) * sizeof (char *));
	if (!to_add)
		return (free_big_tab(tab), NULL);
	ret++;
	while (ret <= pos)
	{
		to_add[j] = ft_strdup(cmds[ret]);
		if (!to_add[j])
			return (free_cmds_tab(tab, to_add, i, j), NULL);
		j++;
		ret++;
	}
	to_add[j] = NULL;
	tab[i] = to_add;
	tab[i + 1] = NULL;
	return (tab);
}

int	has_redir(char	*line, int arg)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (arg == 1 && line[i] == '>')
			return (1);
		if (arg == 0 && line[i] == '<')
			return (1);
		i += (skip_quotes(line, i) + 1);
	}
	return (0);
}

char	***filltab(char ***tab, char **cmds)
{
	int		i;
	int		ret;

	ret = -1;
	i = 0;
	while (cmds[i])
	{
		if (has_redir(cmds[i], 1))
		{
			tab = tab_add(tab, cmds, i, ret);
			if (!tab)
				return (NULL);
			ret = i;
		}
		i++;
	}
	if (i > 0 && cmds[i - 1] && ret != i)
		tab = tab_add(tab, cmds, i - 1, ret);
	return (tab);
}

char	***alloc_tab(int nb)
{
	char	***tab;

	tab = (char ***) malloc((nb + 2) * sizeof (char **));
	if (!tab)
		return (NULL);
	tab[0] = NULL;
	return (tab);
}

char	***init_tab(char **cmds)
{
	int		nb;
	int		i;
	int		j;

	nb = 0;
	i = 0;
	j = 0;
	while (cmds[i])
	{
		while (cmds[i] && cmds[i][j])
		{
			if (cmds[i][j] == '>')
			{
				nb++;
				break ;
			}
			j += (skip_quotes(cmds[i], j) + 1);
		}
		i++;
		j = 0;
	}
	return (alloc_tab(nb));
}

char	***split_cmds(char *line)
{
	char	**cmds;
	char	***res;

	cmds = rmv_pipes(ft_split_quotes(line, '|'));
	if (!cmds)
		return (NULL);
	res = init_tab(cmds);
	if (!res)
		return (ft_freetab(cmds), NULL);
	res = filltab(res, cmds);
	if (!res)
		return (ft_freetab(cmds), NULL);
	ft_freetab(cmds);
	return (res);
}
