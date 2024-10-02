/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:17:38 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/30 16:25:39 by luibarbo         ###   ########.fr       */
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

typedef struct execexec
{
	int		type;
	char	*argv[20];
	char	*end_argv[20];
}	t_execexec;

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
	t_cmd	*left;
	t_cmd	*right;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipecmd;

/* ========================================================================== */
/*	FUNCTIONS                                                                 */
/* ========================================================================== */

void	init_minishell(char *envp[]);
void	signals(void);

char	**copy_env(char **env);
int		env_size(char **env);
void	free_env(char **env);
t_cmd	*parsecmd(char *str);
int		gettoken(char **ptr_str, char *end_str,
			char **start_token, char **end_token);
int		special_chars(char *str);
void	nulterminate(t_cmd *cmd);
int		find_char(char **ptr_str, char *end_str, char *set);
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*redircmd(t_cmd	*next_cmd, char *file, char *end_file, int mode, int fd);

void	runcmd(t_cmd *cmd, char **local_env);
void	execute_commands(t_execcmd *execcmd, char **local_env);

char	*get_cmd_path(char **env, char *cmd);
char	*get_cmds_path(char	*path, char	*cmd);
void	child1_process(t_pipecmd *pipecmd, char **local_env);
void	child2_process(t_pipecmd *pipecmd, char **local_env);
void	fork_function(t_pipecmd *pipecmd, char **local_env);
void	close_all(t_pipecmd *pipecmd);

char	*is_builtin(t_execcmd *execcmd);
void	exec_builtin(char **argv, char *builtin, char **local_env);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_cd(char **argv);
void	ft_export(char **argv, char **local_env);
void	ft_export_no_args(char **local_env);
void	ft_env(char **argv, char **local_env);
int		ft_exit(void);

#endif
