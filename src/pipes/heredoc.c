/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:50:39 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/14 23:24:10 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_heredoc(t_minishell *minishell, char **rets, char *cmd)
{
	int		fd;
	int		ret;
	char	*tmp;

	if (!cmd)
		return (1);
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
	if (minishell->ex_hrd == 1)
		exec_cmd(minishell, cmd);
	return (0);
}

static int	treat_exit(t_minishell *minishell, char *line)
{
	set_g_exit(0);
	if (line)
		line[ft_strlen(line) - 1] = '\0';
	minishell->line = line;
	parse_input(minishell);
	return (1);
}

static int	incr_free(char *line)
{
	free(line);
	return (1);
}

static void	treat_line(char **rets, char *line, int *i)
{
	line[ft_strlen(line) - 1] = '\0';
	rets[*i] = ft_strdup(line);
	(*i) += incr_free(line);
}

int	here_doc(t_minishell *minishell, char *delimiter, char *cmd)
{
	int		i;
	char	*line;
	char	**rets;

	i = 0;
	g_exit = 1;
	rets = (char **)malloc(sizeof(char *) * 1000);
	if (!rets)
		return (get_error(minishell, NULL));
	while (g_exit == 1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (g_exit == 2)
			return (treat_exit(minishell, line));
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		treat_line(rets, line, &i);
	}
	rets[i] = NULL;
	return (exec_heredoc(minishell, rets, cmd));
}
