/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:50:39 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/20 00:38:21 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab, int i)
{
	int	j;
	int	res;

	res = 0;
	j = 0;
	if (!tab)
		return (res);
	while (j < i && tab[j])
	{
		res += ft_strlen(tab[j]);
		j++;
	}
	return (res);
}

static int	exec_heredoc(t_minishell *minishell, char **rets)
{
	int		fd;
	int		ret;
	char	*tmp;

	fd = open("/tmp/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd < 0)
		return (get_error(minishell, NULL));
	ret = 0;
	while (rets[ret])
	{
		tmp = ft_strjoin(rets[ret], "\n");
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		ret++;
	}
	close(fd);
	ft_freetab(rets);
	input(minishell, "/tmp/heredoc");
	return (0);
}

static void	treat_line(char **rets, char *line, int *i)
{
	line[ft_strlen(line) - 1] = '\0';
	rets[*i] = ft_strdup(line);
	free(line);
	(*i) += 1;
}

int	here_doc(t_minishell *minishell, char *delimiter)
{
	int		i;
	char	*line;
	char	**rets;

	i = 0;
	rets = (char **)malloc(sizeof(char *) * 1000);
	if (!rets)
		return (get_error(minishell, NULL));
	while (g_exit == 0)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			if (line)
				free(line);
			else 
				(printf("\nbash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", tab_len(rets, i), delimiter));
			break ;
		}
		treat_line(rets, line, &i);
	}
	rets[i] = NULL;
	return (exec_heredoc(minishell, rets));
}
