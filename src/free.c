/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 04:54:22 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/05 16:49:55 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_minishell *minishell)
{
	close(minishell->original_stdin);
	close(minishell->original_stdout);
	free(minishell->color);
	free(minishell->path);
	ft_freetab(minishell->env);
	rl_clear_history();
	lstclear(&minishell->history, free);
}
