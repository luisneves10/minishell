/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:37:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/01 10:59:20 by luibarbo         ###   ########.fr       */
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
		perror("error fork");
	if (pid == 0)
	{
		// TRATAR EXECUTAVEIS
		/* if (execve(execcmd->argv[0], execcmd->argv, local_env) == -1)
			perror("execve error"); */
		if (execve(path, execcmd->argv, *local_env) == -1)
			perror("execve error");
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
}

void	runcmd(t_cmd *cmd, char ***local_env)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;

	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		execute_commands(execcmd, local_env);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		if (pipe(pipecmd->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		fork_function(pipecmd, *local_env);
		close_all(pipecmd);
	}
}
