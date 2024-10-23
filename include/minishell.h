/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:17:38 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/17 16:21:05 by daduarte         ###   ########.fr       */
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

/* ----------------------------------------------------- CCOMAND MACROS ----- */
# define EXEC  1
# define REDIR 2
# define PIPE  3
# define LIST  4
# define BACK  5

/* ------------------------------------------------------- ERROR MACROS ----- */
# define S_Q     41
# define D_Q     42
# define ERROR_P 43
# define ER_TOK  44
# define E_NWL   45

/* ------------------------------------------------------ EXPAND MACROS ----- */
# define EXPAND_NEW  1
# define EXPAND_APPEND 2

typedef struct cmd
{
	int	type;
}	t_cmd;

typedef struct s_redir
{
	int				type;
	char			*file;
	char			*end_file;
	struct s_redir	*next;
}	t_redir;

typedef struct execcmd
{
	int		type;
	char	*argv[20];
	char	*end_argv[20];
	t_redir	*redir;
	int		fd_out;
	int		fd_in;
}	t_execcmd;

typedef struct pipecmd
{
	int		type;
	int		pipefd[2];
	int		prev_pipe;
	t_cmd	*left;
	t_cmd	*right;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipecmd;

typedef struct token
{
	char	*start;
	char	*end;
	int		argc;
}	t_token;

typedef struct file_descriptors
{
	int	in_fd;
	int	out_fd;
	int	saved_in;
	int	saved_out;
}	t_fds;

typedef struct shell
{
	char	*name;
	char	**env;
	char	*input;
	char	*prompt;
	int		exit_status;
}	t_shell;

/* ========================================================================== */
/* ------------------------------ FUNCTIONS --------------------------------- */
/* ========================================================================== */

/* ========================================================================== */
/*	INITIALIZATION AND SIGNALS                                                */
/* ========================================================================== */
void	init_minishell(t_shell *shell);
void	signals(void);
t_shell	*init_struct(char **argv, char **envp);
void	free_shell(t_shell *shell, int i);

/* ========================================================================== */
/*	ENVIRONMENT UTILS                                                         */
/* ========================================================================== */
char	**copy_env(char **env);
int		env_size(char **env);
void	free_env(char **env);
int		var_name_len(char *var);
int		var_search(char **env, char *var);

/* ========================================================================== */
/*	PARSING                                                                   */
/* ========================================================================== */
t_cmd	*parse_cmd(char *str);
int		get_token(char **ptr_str, char *end_str,
			char **start_token, char **end_token);
int		special_chars(char **str);
void	null_terminate(t_cmd *cmd);
int		find_char(char **ptr_str, char *end_str, char *set);
t_cmd	*exec_cmd(void);
int		syntax_check(char *input);

/* ========================================================================== */
/*	COMMANDS AND REDIRECTIONS                                                 */
/* ========================================================================== */
void	run_cmd(t_cmd *cmd, t_shell *shell);
void	handle_redirs(t_execcmd *execcmd, t_shell *shell);
void	execute_commands(t_execcmd *execcmd, t_shell *shell);
void	free_split(char **split);
void	handle_child_process(char *path, t_execcmd *execcmd, t_shell *shell);
void	handle_parent_process(int pid, char *path,
			t_execcmd *execcmd, t_shell *shell);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_token	*create_token(void);

/* ========================================================================== */
/*	EXECUTION AND PROCESS HANDLING                                            */
/* ========================================================================== */
char	*get_cmd_path(char **env, char *cmd);
char	*get_cmds_path(char *path, char *cmd);
void	child1_process(t_pipecmd *pipecmd, t_shell *shell,
			int prev_pipe, int *pi);
void	fork_function(t_pipecmd *pipecmd, t_shell *shell);
void	close_all(t_pipecmd *pipecmd);

/* ========================================================================== */
/*	MEMORY MANAGEMENT                                                         */
/* ========================================================================== */
void	free_cmd(t_cmd *cmd);

/* ========================================================================== */
/*	BUILTINS                                                                  */
/* ========================================================================== */
char	*is_builtin(t_execcmd *execcmd);
void	exec_builtin(char **argv, char *builtin, t_shell *shell);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_cd(char **argv, t_shell *shell);
int		ft_export(char **argv, t_shell *shell);
char	**update_env(char **local_env, char *var);
int		ft_export_no_args(t_shell *shell);
void	append_var(t_shell *shell, char *var);
int		ft_unset(char **argv, t_shell *shell);
int		ft_env(char **argv, t_shell *shell);
void	ft_exit(char **argv, t_shell *shell);

/* ========================================================================== */
/*	BUILTIN UTILS                                                             */
/* ========================================================================== */
int		has_options(char **argv, char *command);

#endif
