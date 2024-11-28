/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:17:38 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/26 11:19:59 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include <sys/types.h>
# include <sys/wait.h>

/* ----------------------------------------------------- COMMAND MACROS ----- */
# define EXEC  1
# define REDIR 2
# define PIPE  3

/* ------------------------------------------------------ EXPORT MACROS ----- */
# define EXPORT_NEW  1
# define EXPORT_APPEND 2

/* ------------------------------------------------------- EXPAND EMPTY ----- */
# define EXPAND_NULL "\x02"

/* -------------------------------------------------------- EXIT ERRORS ----- */
# define ERR_NUM  1
# define ERR_ARG 2

/* -------------------------------------------------------- EXIT MACROS ----- */
# define EXIT_EOF 10
# define EXIT_CMD 11

/* --------------------------------------------------- TOKEN OR HEREDOC ----- */
# define HEREDOC 1
# define TOKEN 0

extern int	g_ctrlc;

typedef struct s_redir
{
	int				type;
	char			*file;
	char			*end_file;
	struct s_redir	*next;
}	t_redir;

typedef struct heredoc
{
	int				fd;
	int				index;
	char			*filepath;
	char			*delimiter;
	struct heredoc	*next;
}	t_heredoc;

typedef struct cmd
{
	int			type;
	char		**argv;
	t_redir		*redir;
	int			argc;
	int			fd_out;
	int			fd_in;
	t_heredoc	*heredoc;
	t_heredoc	*heredoc_head;
	int			pipefd[2];
	int			prev_pipe;
	struct cmd	*left;
	struct cmd	*right;
	pid_t		pid1;
	pid_t		pid2;
}	t_cmd;

typedef struct s_chunk
{
	char			*str;
	char			type;
	struct s_chunk	*next;
}	t_chunk;

typedef struct token
{
	char	*start;
	char	*end;
	int		argc;
}	t_token;

typedef struct file_descriptors
{
	int	in_fd;
	int	out;
	int	saved_in;
	int	saved_out;
}	t_fds;

typedef struct shell
{
	t_cmd		*head;
	char		*name;
	char		**env;
	char		*input;
	char		*prompt;
	int			ambiguous;
	int			argc;
	int			heredoc_name;
	int			status1;
	int			status2;
	int			home_index;
	int			exit_heredoc;
	int			exit_status;
	int			heredoc_flag;
	t_fds		*fds;
}	t_shell;

/* ========================================================================== */
/* ------------------------------ FUNCTIONS --------------------------------- */
/* ========================================================================== */

/* ========================================================================== */
/*	INITIALIZATION                                                            */
/* ========================================================================== */
void		init_minishell(t_shell *shell);
t_token		*create_token(void);
t_shell		*init_struct(char **argv, char **envp);
t_fds		*init_fds(void);
t_cmd		*create_cmd(t_shell *shell, int type, t_cmd *left, t_cmd *right);

/* ========================================================================== */
/*	SIGNALS                                                                   */
/* ========================================================================== */
void		signals(void);
void		signal_handler(int sig);
void		heredoc_sig_handler(int sig);
void		child_signal_handler(int sig);

/* ========================================================================== */
/*	ENVIRONMENT UTILS                                                         */
/* ========================================================================== */
char		**copy_env(char **env);
int			env_size(char **env);
void		free_env(char **env);
int			var_name_len(char *var);
int			var_search(char **env, char *var);

/* ========================================================================== */
/*	PARSING                                                                   */
/* ========================================================================== */
t_cmd		*parse_cmd(char *str, t_shell *shell);
int			get_token(char **ptr_str, char **start_token, char **end_token);
int			special_chars(char **str);
int			find_char(char **ptr_str, char *set);
int			syntax_check(t_shell *shell);
void		token_count(char *str, t_shell *argc);
t_redir		*add_redir(t_redir *head, int type, t_token *tok, t_shell *shell);
int			deal_token(t_cmd *cmd, char **str,
				t_token *token, t_shell *shell);
char		*clean_token(char *tok, t_shell *shell, int type);
int			final_token_size(t_chunk *chunks);
t_chunk		*chunk_last(t_chunk *chunk);
void		chunk_add_back(t_chunk **chunks, t_chunk *chunk, t_chunk **head);
char		*chunks_join(t_chunk *chunks, t_shell *shell);
void		free_chunks(t_chunk *chunks);
char		**clean_argv(t_cmd *cmd);

/* ========================================================================== */
/*	EXPANSIONS                                                                */
/* ========================================================================== */
char		*deal_expansion(char *token, t_shell *shell);
char		*expansion_join(char *token, char *old_final, int *i);
char		*expand_cases(char **token, t_shell *shell);
char		*create_expand(char *expand);

/* ========================================================================== */
/*	COMMANDS                                                                  */
/* ========================================================================== */
void		run_cmd(t_cmd *cmd, t_shell *shell);
void		execute_commands(t_cmd *execcmd, t_shell *shell);
void		handle_child_process(char *path, t_cmd *execcmd,
				t_shell *shell);
void		handle_parent_process(int pid, char *path,
				t_cmd *execcmd, t_shell *shell);
int			fork_function1(t_cmd *pipecmd, t_shell *shell);
int			fork_function2(t_cmd *pipecmd, t_shell *shell);
void		wait_pipes_close(t_cmd *cmd, t_shell *shell, int pid1, int pid2);
char		*get_cmd_path(char **env, char *cmd);
char		*get_cmds_path(char *path, char *cmd);
int			is_directory(char *path);
void		path_errors(t_shell *shell, t_cmd *cmd);
int			has_slash(char *arg);

/* ========================================================================== */
/*	REDIRECTIONS                                                              */
/* ========================================================================== */
void		handle_redirs(t_cmd *execcmd, t_shell *shell);
int			handle_heredoc(t_cmd *cmd, t_shell *shell);
int			heredoc_loop(t_heredoc *curr, t_shell *shell);
int			process_heredoc(t_heredoc *curr, t_shell *shell);
t_heredoc	*get_delimiter(char *start_tok, char *end_tok,
				t_shell *shell, t_cmd *cmd);
int			special_redirs(char **str);
int			ambigous_redir(t_shell *shell, t_redir *redir);
int			file_permissions(t_shell *shell, t_redir *redir);
int			valid_redir(t_shell *shell, t_redir *redir, t_cmd *cmd);
int			redirs_in(t_fds *fds, t_redir *redir, t_shell *shell, t_cmd *cmd);
int			redirs_out(t_fds *fds, t_redir *redir, t_shell *shell);
void		close_fds(t_fds *fds);

/* ========================================================================== */
/*	MEMORY MANAGEMENT                                                         */
/* ========================================================================== */
void		free_cmd(t_cmd *cmd);
void		delete_heredocs(t_shell *shell, int flag, t_cmd *cmd);
void		free_split(char **split);
void		free_shell(t_shell *shell, int i);

/* ========================================================================== */
/*	BUILTINS                                                                  */
/* ========================================================================== */
char		*is_builtin(t_cmd *execcmd);
void		exec_builtin(char **argv, char *builtin, t_shell *shell);
int			ft_echo(char **argv);
int			ft_pwd(char **argv);
int			ft_cd(char **argv, t_shell *shell);
int			var_is_set(char **local_env, char *var);
int			update_var(t_shell *shell, char *var_name, char *var_value);
int			ft_export(char **argv, t_shell *shell);
char		**update_env(char **local_env, char *var);
int			ft_export_no_args(t_shell *shell);
void		append_var(t_shell *shell, char *var);
int			ft_unset(char **argv, t_shell *shell);
int			ft_env(char **argv, t_shell *shell);
void		ft_exit(char **argv, t_shell *shell);
int			exit_error(char *arg, int error);
int			valid_code(char *arg);
int			has_options(char **argv, char *command);

/* ========================================================================== */
/*	UTILS                                                                     */
/* ========================================================================== */
int			mini_error(char *str, int error, t_shell *shell);
int			is_whitespace(char c);
void		on_off_flag(int *flag);

#endif
