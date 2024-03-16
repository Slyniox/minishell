/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:29:29 by balt              #+#    #+#             */
/*   Updated: 2024/03/14 23:17:58 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(t_minishell *minishell)
{
	if (!minishell->line)
		return ;
	if (is_empty(minishell->line) || has_double_pipes(minishell->line)
		|| start_pipes(minishell->line))
	{
		if (has_double_pipes(minishell->line) || start_pipes(minishell->line))
			printf("Error: Parsing error around \"|\" token\n");
		minishell->line = NULL;
		return (free(minishell->line));
	}
	minishell->line = replace_vals(minishell, minishell->line);
	if (!minishell->line)
	{
		printf("Error: Parsing error while replacing env varibales\n");
		return ;
	}
	minishell->line = rmv_double_pipes(minishell->line);
	//minishell->line = remove_redirections(minishell, minishell->line, 1);
	if (!minishell->line)
	{
		printf("Error: Parsing error while treating redirections\n");
		return ;
	}
	minishell->line = rmv_double_pipes(minishell->line);
	minishell->line = rmv_double_spaces(minishell->line);
}
