/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:00 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/18 03:17:49 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(t_minishell *minishell, char *file)
{
	int	fd;
	int	ret;

	fd = open(file, O_RDONLY, 0777);
	ret = access(file, F_OK | R_OK);
	if (fd < 0 || ret < 0)
		return (get_error(minishell, NULL));
	dup2(fd, STDIN_FILENO);
	minishell->reset_input = true;
	close(fd);
	return (0);
}

int	output(t_minishell *minishell, char *file)
{
	int	fd;
	int	ret;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	ret = access(file, F_OK | W_OK);
	if (fd < 0 || ret < 0)
		return (get_error(minishell, NULL));
	dup2(fd, STDOUT_FILENO);
	minishell->reset_output = true;
	close(fd);
	return (0);
}

static int	append(t_minishell *minishell, char *file)
{
	int	fd;
	int	ret;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	ret = access(file, F_OK | W_OK);
	if (fd < 0 || ret < 0)
		return (get_error(minishell, NULL));
	dup2(fd, STDOUT_FILENO);
	minishell->reset_output = true;
	close(fd);
	return (0);
}

int	exec_redirect(t_minishell *minishell, char *line, char *cmd,
		t_redirect_code code)
{
	if (code == INPUT)
		return (input(minishell, line));
	else if (code == OUTPUT)
		return (output(minishell, line));
	else if (code == HEREDOC)
		return (here_doc(minishell, line, cmd));
	else if (code == APPEND)
		return (append(minishell, line));
	else
		return (1);
}
