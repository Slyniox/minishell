/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:11:22 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/19 21:08:50 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include "../libft/libft.h"

# define RESET "\033[0;39m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define PURPLE "\033[1;35m"
# define PINK "\033[1;38;5;200m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

typedef enum e_redirect_code
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redirect_code;

typedef struct s_history
{
	char				*cmd;
	struct s_history	*next;
}	t_history;

typedef struct s_minishell
{
	int			is_init_cmds;
	int			ex_hrd;
	int			ret;
	int			ac;
	int			original_stdin;
	int			original_stdout;
	bool		exit;
	bool		reset_input;
	bool		reset_output;
	bool		force_error;
	char		*color;
	char		*line;
	char		*path;
	char		**env;
	char		**av;
	char		***cmds;
	t_history	*history;
}	t_minishell;

extern int	g_exit;

void			free_all(t_minishell *minishell);
int				get_error(t_minishell *minishell, char *error);
void			init(t_minishell *minishell, int ac, char **av, char **env);
void			parse(t_minishell *minishell);

// Pipes
int				exec_cmd(t_minishell *minishell, char *line);
char			**get_path_dirs(char **env);
char			*get_cmd_path(char *cmd, char **env);
int				here_doc(t_minishell *minishell, char *delimiter);
int				exec_redirect(t_minishell *minishell, char *line,
					t_redirect_code code);
bool			builtins(t_minishell *minishell, char *cmd);
int				run_cmd(t_minishell *minishell, char *cmd_name);
int				run_single_cmd(t_minishell *minishell, char *cmd_name,
					char ***cmds, int *original_fd);
int				create_pipe(t_minishell *minishell, char ***cmds, int j, int i,
					int *original_fd);
char			**ft_split_quotes(char *s, char c);
char			*ft_filltab(char *line, char c, int pos);
char			***split_cmds(char *line);
void			free_cmds_tab(char ***tab, char **to_add,
					int tab_size, int add_size);
void			*free_big_tab(char ***tab);
void			*fbtn(char ***tab, int j, int i);
// Redirections
int				input(t_minishell *minishell, char *file);

// Builtins
int				ft_cd(t_minishell *minishell);
int				ft_echo(t_minishell *minishell, char *cmd);
int				ft_env(t_minishell *minishell);
int				ft_exit(t_minishell *minishell, char *args);
int				ft_export(t_minishell *minishell, char *arg);
int				ft_pwd(t_minishell *minishell);
int				ft_unset(t_minishell *minishell, char *arg);
// Others
int				ft_history(t_minishell *minishell);
int				ft_poney(void);
int				ft_bonjour(t_minishell *minishell, char *login);
int				ft_setcolor(t_minishell *minishell, char *color);

// Utils
// Lists
void			reset_fds(t_minishell *minishell);
void			lstclear(t_history **lst, void (*del)(void *));
void			lstdelone(t_history *lst, void (*del)(void *));
void			lstadd_back(t_history **lst, t_history *new);
t_history		*lstlast(t_history *lst);
t_history		*lstnew(char *cmd);
// Path
bool			check_cd_shortcut(char *cmd);
char			*get_env(t_minishell *minishell, char *value);
// Values
void			set_g_exit(int value);
bool			valid(char c);

// Parsing
int				update_pos(char *line);
char			*cut_heredoc(char *line, int pos, char *value);
char			*rmv_char(char *line, int pos);
char			*rmv_first_char(char *line, char to_rmv, int size);
char			*rmv_alone_quotes(char *line);
char			*trimline(char *line, int pos, int rv);
char			*rmv_double_spaces(char *line);
void			parse_input(t_minishell *minishell);
int				smart_skipper(char *line, int pos, int nb1, int nb2);
int				in_quotes(char *line, int pos);
int				skip_quotes(char *line, int pos);
int				is_sep(char c, int pos);
int				check_for_path(char *line, int pos);
char			*replace_path(t_minishell *minishell, char *line, int pos);
char			*surplus(char *line, int pos, char *val_name);
char			*add_val(char *line, int pos, char *val);
char			*insert_val(t_minishell *minishell, char *line, int pos,
					char *val_name);
char			*line_add_val(t_minishell *minishell, char *line, int pos);
char			*replace_vals(t_minishell *minishell, char *line);
char			*remove_redirections(t_minishell *minishell, char *line,int arg);
char			*treat_redirect(t_minishell *minishell, char *line, int pos);
char			*get_redir_value(char *line, int pos);
int				is_token_nc(char *line, int pos, int arg);
int				is_space(char c);
int				is_empty(char *line);
int				has_double_pipes(char *line);
char			*rmv_double_pipes(char *line);
char			*before_redir(char *line, int pos, char *value);
void			action(int signum);
int				start_pipes(char *line);
char			*ft_fill(char *line, char *tab, int i, int pos);
int				prev_heredoc(char *line, int pos);
char			*rmv_useless(char *line);
char			*rmv_pipeline(char *line);
char			**rmv_pipes(char **tab);
char			**free_useless(char **tab);
char			*rmv_val(t_minishell *minishell, int pos, char *val_name);
t_redirect_code	sign_id(char *line, int pos, int redir_input);

#endif