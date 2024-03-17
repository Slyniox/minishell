/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:08:59 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/16 17:15:23 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_minishell *minishell)
{
	if (!minishell->line || !minishell->line[0]
		|| minishell->line[0] == '\0')
		return ;
	parse_input(minishell);
	if (!minishell->line || !minishell->line[0]
		|| minishell->line[0] == '\0')
		return ;
	exec_cmd(minishell, NULL);
	lstadd_back(&minishell->history, lstnew(minishell->line));
}
