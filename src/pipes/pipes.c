/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:39:01 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/20 00:41:22 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_heredoc(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if ((line[i] == '<' && line[i + 1] && line[i + 1] == '<'))
			return (1);
		i++;
		i += skip_quotes(line, i);
	}
	return (0);
}

bool	builtins(t_minishell *minishell, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && valid(cmd[4]))
		minishell->ret = ft_echo(minishell, cmd);
	else if (check_cd_shortcut(cmd))
		minishell->ret = ft_cd(minishell);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && valid(cmd[3]))
		minishell->ret = ft_pwd(minishell);
	else if (ft_strncmp(cmd, "export", 6) == 0 && valid(cmd[6]))
		minishell->ret = ft_export(minishell, cmd + 7);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && valid(cmd[5]))
		minishell->ret = ft_unset(minishell, cmd + 6);
	else if (ft_strncmp(cmd, "env", 3) == 0 && valid(cmd[3]))
		minishell->ret = ft_env(minishell);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && valid(cmd[4]))
		minishell->ret = ft_exit(minishell, cmd);
	else if (ft_strncmp(cmd, "bonjour", 7) == 0 && valid(cmd[7]))
		minishell->ret = ft_bonjour(minishell, cmd + 8);
	else if (ft_strncmp(cmd, "poney", 5) == 0 && valid(cmd[5]))
		minishell->ret = ft_poney();
	else if (ft_strncmp(cmd, "setcolor", 8) == 0 && valid(cmd[8]))
		minishell->ret = ft_setcolor(minishell, cmd + 9);
	else if (ft_strncmp(cmd, "history", 7) == 0 && valid(cmd[7]))
		minishell->ret = ft_history(minishell);
	else
		return (false);
	return (true);
}

int	run_cmd(t_minishell *minishell, char *cmd_name)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(cmd_name, ' ');
	cmd_path = get_cmd_path(cmd[0], minishell->env);
	if (!cmd_path)
	{
		ft_freetab(cmd);
		get_error(minishell, "Command not found");
		return (-1);
	}
	if (execve(cmd_path, cmd, minishell->env) == -1)
	{
		ft_freetab(cmd);
		free(cmd_path);
		get_error(minishell, NULL);
		return (-1);
	}
	ft_freetab(cmd);
	free(cmd_path);
	return (0);
}

int	run_single_cmd(t_minishell *minishell, char *cmd_name, char ***cmds,
		int *original_fd)
{
	int			fds[2];
	pid_t		pid;

	if (!builtins(minishell, cmd_name))
	{
		set_g_exit(3);
		if (pipe(fds) < 0)
			return (close(fds[0]), close(fds[1]), get_error(minishell, NULL));
		pid = fork();
		if (pid < 0)
			return (close(fds[0]), close(fds[1]), get_error(minishell, NULL));
		if (pid == 0)
		{
			(close(fds[0]), close(fds[1]));
			if (*original_fd != STDIN_FILENO)
				close(*original_fd);
			if (run_cmd(minishell, cmd_name) == -1)
				(free_all(minishell), free_big_tab(cmds), exit(EXIT_FAILURE));
			(free_big_tab(cmds), free_all(minishell), exit(EXIT_SUCCESS));
		}
		if (*original_fd != STDIN_FILENO)
			close(*original_fd);
		(close(fds[0]), close(fds[1]), wait(&pid));
	}
	return (0);
}

int	create_pipe(t_minishell *minishell, char ***cmds, int j, int i, int *original_fd)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) < 0)
		return (close(fds[0]), close(fds[1]), get_error(minishell, NULL));
	pid = fork();
	if (pid < 0)
		return (close(fds[0]), close(fds[1]), get_error(minishell, NULL));
	if (pid == 0)
	{
		dup2(*original_fd, STDIN_FILENO);
		if (cmds[j][i + 1] != NULL)
			dup2(fds[1], STDOUT_FILENO);
		(close(fds[0]), close(fds[1]));
		if (*original_fd != STDIN_FILENO)
			close(*original_fd);
		cmds[j][i] = remove_redirections(minishell, cmds[j][i], 0);
		if (!cmds[j][i])
			(free_all(minishell), fbtn(cmds, j, i), exit(EXIT_FAILURE));
		if (run_single_cmd(minishell, cmds[j][i], cmds, original_fd) == -1)
			(free_all(minishell), free_big_tab(cmds), exit(EXIT_FAILURE));
		(free_big_tab(cmds), free_all(minishell), exit(EXIT_SUCCESS));
	}
	if (*original_fd != STDIN_FILENO)
		close(*original_fd);
	waitpid(pid, NULL, 0);
	*original_fd = fds[0];
	return (close(fds[1]), 0);
}

int	exec_cmd(t_minishell *minishell, char *line)
{
	int		i;
	int		j;
	int		original_fd;

	original_fd = STDIN_FILENO;
	g_exit = 0;
	i = -1;
	j = 0;
	minishell->ex_hrd = 1;
	if (line)
		minishell->cmds = split_cmds(line);
	else
		minishell->cmds = split_cmds(minishell->line);
	if (!minishell->cmds)
		return (get_error(minishell, NULL));
	if (!minishell->cmds[0][1] && !minishell->cmds[1])
	{
		minishell->cmds[0][0] = remove_redirections(minishell, minishell->cmds[0][0], 0);
		if (!minishell->cmds[0][0] || !minishell->cmds[0][0][0] || g_exit == 1)
			return(free_big_tab(minishell->cmds), -1);
		if (run_single_cmd(minishell, minishell->cmds[0][0], minishell->cmds, &original_fd) == -1)
			return (free_big_tab(minishell->cmds), set_g_exit(0), -1);
		return (set_g_exit(0), free_big_tab(minishell->cmds), 0);
	}
	while (minishell->cmds[j])
	{
		i = -1;
		while (minishell->cmds[j][++i])
		{
			if (minishell->cmds[j][i + 1] && has_heredoc(minishell->cmds[j][i]))
				minishell->ex_hrd = 0;
			minishell->cmds[j][i] = remove_redirections(minishell, minishell->cmds[j][i], 1);
			if (g_exit == 1)
				return (free_big_tab(minishell->cmds), -1);
			if (create_pipe(minishell, minishell->cmds, j, i, &original_fd) == -1)
				return (free_big_tab(minishell->cmds), -1);
		}
		j++;
	}
	close(original_fd);
	return (free_big_tab(minishell->cmds), 0);
}
