/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:17:38 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/16 10:24:41 by daduarte         ###   ########.fr       */
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

# define EXEC  1
# define REDIR 2
# define PIPE  3
# define LIST  4
# define BACK  5

typedef struct cmd
{
	int	type;
}	t_cmd;

typedef struct execcmd
{
	int		type;
	char	*argv[20];
	char	*end_argv[20];
}	t_execcmd;

typedef struct redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
}	t_redircmd;

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
}	t_token;

/* ========================================================================== */
/*	FUNCTIONS                                                                 */
/* ========================================================================== */

void	init_minishell(char *envp[]);
void	signals(void);

/* ---------------------------------------------------------- ENV UTILS ----- */
char	**copy_env(char **env);
int		env_size(char **env);
void	free_env(char **env);

int		var_name_len(char *var);
int		var_search(char **env, char *var);

/* ---------------------------------------------------------- _________ ----- */
t_cmd	*parse_cmd(char *str);
int		get_token(char **ptr_str, char *end_str,
			char **start_token, char **end_token);
int		special_chars(char *str);
void	null_terminate(t_cmd *cmd);
int		find_char(char **ptr_str, char *end_str, char *set);
t_cmd	*exec_cmd(void);
void	redirect_cmd(t_redircmd *redircmd, char ***local_env);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*redir_cmd(t_cmd	*next_cmd, t_token *tok, int mode, int fd);
t_token	*create_token(void);
int		syntax_check(char *input);

void	run_cmd(t_cmd *cmd, char ***local_env);
void	execute_commands(t_execcmd *execcmd, char ***local_env);

char	*get_cmd_path(char **env, char *cmd);

char	*get_cmds_path(char *path, char *cmd);
void	child1_process(t_pipecmd *pipecmd, char ***local_env,
			int prev_pipe, int *pi);
void	fork_function(t_pipecmd *pipecmd, char ***local_env);
void	free_cmd(t_cmd *cmd);
void	close_all(t_pipecmd *pipecmd);

/* ----------------------------------------------------------- BUILTINS ----- */
char	*is_builtin(t_execcmd *execcmd);
void	exec_builtin(char **argv, char *builtin, char ***local_env);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_cd(char **argv, char ***local_env);
int		ft_export(char **argv, char ***local_env);
void	ft_export_no_args(char **local_env);
int		ft_unset(char **argv, char ***local_env);
int		ft_env(char **argv, char **local_env);
int		ft_exit(void);
/* ------------------------------------------------------ BUILTIN UTILS ----- */
int		has_options(char **argv, char *command);

#endif
