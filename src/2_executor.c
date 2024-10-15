/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:37:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/15 12:26:47 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmds_path(char	*path, char	*cmd)
{
	int		i;
	char	*true_cmd = NULL;
	char	*full_path;
	char	**directory;

	i = 0;
	true_cmd = ft_strjoin("/", cmd);
	directory = ft_split(path, ':');
	if (!directory)
		return (NULL);
	while (directory[i])
	{
		full_path = ft_strjoin(directory[i], true_cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(true_cmd);
			return (full_path);
		}
		free(full_path);
		i ++;
	}
	free(true_cmd);
	return (NULL);
}

char	*get_cmd_path(char **env, char *cmd)
{
	int		i;
	char	*path;
	char	*real_path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i ++;
	}
	real_path = get_cmds_path(path, cmd);
	free(path);
	if (!real_path)
		return (NULL);
	return (real_path);
}

void	execute_commands(t_execcmd *execcmd, char ***local_env)
{
	int	pid;
	char *path;

	if (is_builtin(execcmd) != NULL)
	{
		exec_builtin(execcmd->argv, is_builtin(execcmd), local_env);
		return ;
	}
	path = get_cmd_path(*local_env, execcmd->argv[0]);
	if (!path)
	{
		printf("%s: command not found\n", execcmd->argv[0]);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("error fork");
		exit(1);
	}
	if (pid == 0)
	{
		// TRATAR EXECUTAVEIS
		/* if (execve(execcmd->argv[0], execcmd->argv, local_env) == -1)
			perror("execve error"); */
		if (execve(path, execcmd->argv, *local_env) == -1)
			perror("execve error");
		exit(1);
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
}

void	redirect_cmd(t_redircmd *redircmd, char ***local_env)
{
	t_execcmd	*execcmd;
	int	saved_fd_in;
	int	saved_fd_out;

	saved_fd_in = dup(STDIN_FILENO);
	saved_fd_out = dup(STDOUT_FILENO);

	if (redircmd->mode & O_WRONLY)
	{
		redircmd->fd = open(redircmd->file, redircmd->mode, 0644);
		if (redircmd->fd < 0)
		{
			perror("redir");
			return ;
		}
		execcmd = (t_execcmd *)redircmd->cmd;
		dup2(redircmd->fd, STDOUT_FILENO);
		close(redircmd->fd);
		nulterminate((t_cmd *)execcmd);
		execute_commands(execcmd, local_env);
	}
	else
	{
		redircmd->fd = open(redircmd->file, O_RDONLY);
		printf("file: %s\n", redircmd->file);
		if (redircmd->fd < 0)
		{
			perror("redir");
			return ;
		}
		dup2(redircmd->fd, STDIN_FILENO);
		close(redircmd->fd);
		execcmd = (t_execcmd *)redircmd->cmd;
		nulterminate((t_cmd *)execcmd);
		execute_commands(execcmd, local_env);
	}
	dup2(saved_fd_out, STDOUT_FILENO);
	dup2(saved_fd_in, STDIN_FILENO);
	close(saved_fd_in);
	close(saved_fd_out);
}

void	runcmd(t_cmd *cmd, char ***local_env)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;
	t_redircmd	*redircmd;

	execcmd = (t_execcmd *)cmd;
	pipecmd = (t_pipecmd *)cmd;
	redircmd = (t_redircmd *)cmd;
	if (cmd == NULL)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		execute_commands(execcmd, local_env);
	}
	else if (cmd->type == PIPE)
	{
		if (pipe(pipecmd->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		fork_function(pipecmd, local_env);
		close_all(pipecmd);
	}
	else if (cmd->type == REDIR)
		redirect_cmd(redircmd, local_env);
}
