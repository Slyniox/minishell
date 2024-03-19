/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:14:39 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/20 00:23:04 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

static char	**get_prompt(t_minishell *minishell)
{
	char	*pwd;
	char	**rets;
	char	**tab;

	rets = (char **)malloc(sizeof(char *) * 6);
	if (!rets)
		return (NULL);
	if (minishell->ret == -1)
		rets[0] = ft_strdup("\033[1;31m・\033[0;39m");
	else
		rets[0] = ft_strdup("\033[1;32m・\033[0;39m");
	pwd = getcwd(NULL, 0);
	tab = ft_split(pwd, '/');
	if (!tab || !tab[0])
		(ft_freetab(tab), tab = (char **)malloc(sizeof(char *) * 2),
			tab[0] = ft_strdup("/"), tab[1] = NULL);
	rets[1] = ft_strdup(minishell->color);
	rets[2] = ft_strdup(tab[ft_tabsize(tab) - 1]);
	rets[3] = ft_strdup("$> ");
	rets[4] = ft_strdup(RESET);
	rets[5] = NULL;
	if (!rets[1] || !rets[2] || !rets[3] || !rets[4])
		return (free(pwd), ft_freetab(rets), ft_freetab(tab), NULL);
	return (free(pwd), ft_freetab(tab), rets);
}

void	reset_fds(t_minishell *minishell)
{
	if (minishell->reset_input == true)
	{
		dup2(minishell->original_stdin, STDIN_FILENO);
		minishell->reset_input = false;
	}
	if (minishell->reset_output == true)
	{
		dup2(minishell->original_stdout, STDOUT_FILENO);
		minishell->reset_output = false;
	}
}

int	main(int ac, char **av, char **env)
{
	char		**rets;
	char		*prompt;
	t_minishell	minishell;

	init(&minishell, ac, av, env);
	while (minishell.exit == false)
	{
		signal(SIGINT, action);
		signal(SIGQUIT, SIG_IGN);
		rets = get_prompt(&minishell);
		prompt = ft_tabjoin(rets, true);
		ft_freetab(rets);
		minishell.line = readline(prompt);
		if (!minishell.line)
			return (free(prompt), free_all(&minishell), exit(0), 0);
		free(prompt);
		add_history(minishell.line);
		parse(&minishell);
		free(minishell.line);
		reset_fds(&minishell);
	}
	free_all(&minishell);
	return (0);
}
