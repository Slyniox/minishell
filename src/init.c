/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:03:26 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/19 23:45:05 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_minishell *minishell, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_exit = 0;
	minishell->original_stdin = dup(STDIN_FILENO);
	minishell->original_stdout = dup(STDOUT_FILENO);
	minishell->ret = 0;
	minishell->exit = false;
	minishell->reset_input = false;
	minishell->reset_output = false;
	minishell->line = NULL;
	minishell->color = ft_strdup(BLUE);
	if (!minishell->color)
		exit(EXIT_FAILURE);
	minishell->env = ft_tabdup(env);
	if (!minishell->env)
		exit(EXIT_FAILURE);
	minishell->path = getcwd(NULL, 0);
	minishell->is_init_cmds = 0;
	minishell->cmds = NULL;
	minishell->history = NULL;
}
