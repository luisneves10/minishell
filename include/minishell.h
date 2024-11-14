/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:17:38 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/14 16:22:11 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
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
# define LIST  4
# define BACK  5

/* ------------------------------------------------------ EXPORT MACROS ----- */
# define EXPORT_NEW  1
# define EXPORT_APPEND 2

/* ------------------------------------------------------ EXPAND MACROS ----- */
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

typedef struct cmd
{
	int			type;
	char		**argv;
	t_redir		*redir;
	int			argc;
	int			fd_out;
	int			fd_in;
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

typedef struct heredoc
{
	int				fd;
	int				index;
	char			*filepath;
	char			*delimiter;
	struct heredoc	*next;
}	t_heredoc;

typedef struct shell
{
	t_cmd		*head;
	char		*name;
	char		**env;
	char		*input;
	char		*prompt;
	int			ambiguous;
	int			argc;
	int			status1;
	int			status2;
	int			exit_heredoc;
	int			exit_status;
	int			heredoc_flag;
	t_heredoc	*heredoc;
	t_heredoc	*heredoc_head;
	t_fds		*fds;
}	t_shell;


void	child_signal_handler(int sig);
/* ========================================================================== */
/* ------------------------------ FUNCTIONS --------------------------------- */
/* ========================================================================== */
int			mini_error(char *str, int error, t_shell *shell);
void		close_fds(t_fds *fds);
int			is_whitespace(char c);
int			is_directory(char *path);
void		path_errors(t_shell *shell, t_cmd *cmd);
void		wait_pipes_close(t_cmd *cmd, t_shell *shell, int pid1, int pid2);
char		**clean_argv(t_cmd *cmd);

/* ========================================================================== */
/* ------------------------------ EXPANSIONS ---------------------------------*/
/* ========================================================================== */
char		*deal_expansion(char *token, t_shell *shell);
void		on_off_flag(int *flag);
char		*expansion_join(char *token, char *old_final, int *i);
char		*expand_cases(char **token, t_shell *shell);
char		*create_expand(char *expand);

/* ========================================================================== */
/*	INITIALIZATION AND SIGNALS                                                */
/* ========================================================================== */
void		init_minishell(t_shell *shell);
t_token		*create_token(void);
void		signals(void);
t_shell		*init_struct(char **argv, char **envp);
void		free_shell(t_shell *shell, int i);
t_fds		*init_fds(void);
void		signal_handler(int sig);
void		heredoc_sig_handler(int sig);
t_cmd		*create_cmd(t_shell *shell, int type, t_cmd *left, t_cmd *right);

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

/* ========================================================================== */
/*	REDIRECTIONS                                                              */
/* ========================================================================== */
void		handle_redirs(t_cmd *execcmd, t_shell *shell);
int			handle_heredoc(t_shell *shell);
t_heredoc	*get_delimiter(char *start_tok, char *end_tok, t_shell *shell);
int			special_redirs(char **str);
int			ambigous_redir(t_shell *shell, t_redir *redir);
int			file_permissions(t_shell *shell, t_redir *redir);
int			valid_redir(t_shell *shell, t_redir *redir);
int			redirs_in(t_fds *fds, t_redir *redir, t_shell *shell);
int			redirs_out(t_fds *fds, t_redir *redir, t_shell *shell);

/* ========================================================================== */
/*	EXECUTION AND PROCESS HANDLING                                            */
/* ========================================================================== */
char		*get_cmd_path(char **env, char *cmd);
char		*get_cmds_path(char *path, char *cmd);

/* ========================================================================== */
/*	MEMORY MANAGEMENT                                                         */
/* ========================================================================== */
void		free_cmd(t_cmd *cmd);
void		delete_heredocs(t_shell *shell, int flag);
void		free_split(char **split);

/* ========================================================================== */
/*	BUILTINS                                                                  */
/* ========================================================================== */
char		*is_builtin(t_cmd *execcmd);
void		exec_builtin(char **argv, char *builtin, t_shell *shell);
int			ft_echo(char **argv);
int			ft_pwd(char **argv);
int			ft_cd(char **argv, t_shell *shell);
int			ft_export(char **argv, t_shell *shell);
char		**update_env(char **local_env, char *var);
int			ft_export_no_args(t_shell *shell);
void		append_var(t_shell *shell, char *var);
int			ft_unset(char **argv, t_shell *shell);
int			ft_env(char **argv, t_shell *shell);
void		ft_exit(char **argv, t_shell *shell);

/* ========================================================================== */
/*	BUILTIN UTILS                                                             */
/* ========================================================================== */
int			has_options(char **argv, char *command);

#endif
