/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:37:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/01 12:09:20 by daduarte         ###   ########.fr       */
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

void	execute_commands(t_execcmd *execcmd, char *envp[])
{
	int	pid;

	//printf("command: %s\n", execcmd->argv[0]);
	if (ft_strncmp(execcmd->argv[0], "cd", 2) == 0)
	{
		ft_cd(execcmd->argv);
		return ;
	}
	if (ft_strncmp(execcmd->argv[0], "pwd", 3) == 0)
	{
		ft_pwd(execcmd->argv);
		return ;
	}
	pid = fork();
	if (pid < 0)
		perror("error fork");
	if (pid == 0)
	{
		// TRATAR EXECUTAVEIS
		/* if (execve(execcmd->argv[0], execcmd->argv, envp) == -1)
			perror("execve error"); */
		char *path = get_cmd_path(envp, execcmd->argv[0]);
		if (execve(path, execcmd->argv, envp) == -1)
			perror("execve error");
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
}

void	redirect_cmd(t_redircmd *redircmd, char *envp[])
{
	t_execcmd	*execcmd;
	int	saved_fd;

	if (redircmd->mode == (O_WRONLY | O_CREAT))
	{
		redircmd->fd = open(redircmd->file, redircmd->mode, 0777);
		if (redircmd->fd < 0)
			perror("redir");
		saved_fd = dup(STDOUT_FILENO);
		dup2(redircmd->fd, STDOUT_FILENO);
		close(redircmd->fd);
		execcmd = (t_execcmd *)redircmd->cmd;
		nulterminate((t_cmd *)execcmd);
		execute_commands(execcmd, envp);
		dup2(saved_fd, STDOUT_FILENO);
		close(saved_fd);
	}
	else
	{
		redircmd->fd = open(redircmd->file, O_RDONLY);
		if (redircmd->fd < 0)
			perror("redir");
		saved_fd = dup(STDIN_FILENO);
		dup2(redircmd->fd, STDIN_FILENO);
		close(redircmd->fd);
		execcmd = (t_execcmd *)redircmd->cmd;
		nulterminate((t_cmd *)execcmd);
		execute_commands(execcmd, envp);
		dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
	}
}

void	runcmd(t_cmd *cmd, char *envp[])
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;
	t_redircmd	*redircmd;

	execcmd = (t_execcmd *)cmd;
	pipecmd = (t_pipecmd *)cmd;
	redircmd = (t_redircmd *)cmd;
	if (cmd->type == EXEC)
		execute_commands(execcmd, envp);
	else if (cmd->type == PIPE)
	{
		if (pipe(pipecmd->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		fork_function(pipecmd, envp);
		close_all(pipecmd);
	}
	else if (cmd->type == REDIR)
	{
		redirect_cmd(redircmd, envp);
	}
}
