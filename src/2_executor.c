/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:37:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/17 16:22:26 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;
	i = 0;

	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

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
			free_split(directory);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(true_cmd);
	free_split(directory);
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
		i++;
	}
	real_path = get_cmds_path(path, cmd);
	free(path);
	if (!real_path)
		return (NULL);
	return (real_path);
}

void	command_type(t_execcmd *execcmd, t_shell *shell, char **path)
{
	if (is_builtin(execcmd) != NULL)
	{
		exec_builtin(execcmd->argv, is_builtin(execcmd), shell);
		*path = NULL;
		return ;
	}
	if (execcmd->argv[0][0] == '/' || ft_strncmp(execcmd->argv[0], "./", 2) == 0
		|| ft_strncmp(execcmd->argv[0], "../", 3) == 0)
		*path = execcmd->argv[0]; //usa o comando como path (ex: ./minishell)
	else
	{
		*path = get_cmd_path(shell->env, execcmd->argv[0]);
		if (!path)
		{
			printf("%s: command not found\n", execcmd->argv[0]);
			return;
		}
	}
}

void	execute_commands(t_execcmd *execcmd, t_shell *shell)
{
	int		pid;
	char	*path;

	command_type(execcmd, shell, &path);
	if (path == NULL)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("error fork");
		exit(1);
	}
	if (pid == 0)
	{
		execve(path, execcmd->argv, shell->env);
		perror("execve error");
		exit(1); //free aqui em caso de erro
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (path != execcmd->argv[0]) //free se o path for criado com malloc
			free(path);
	}
}

void run_cmd(t_cmd *cmd, t_shell *shell)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;

	execcmd = (t_execcmd *)cmd;
	pipecmd = (t_pipecmd *)cmd;
	if (!cmd)
		return;
	if (cmd->type == EXEC)
		handle_redirs(execcmd, shell);
	else if (cmd->type == PIPE)
	{
		if (pipe(pipecmd->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		if (fork() == 0)
		{
			close(pipecmd->pipefd[0]);
			dup2(pipecmd->pipefd[1], STDOUT_FILENO);
			close(pipecmd->pipefd[1]);
			run_cmd(pipecmd->left, shell);// RECURSAO LADO ESQUERDO PIPE
			free_cmd(cmd);
			exit(0);
		}
		if (fork() == 0)
		{
			close(pipecmd->pipefd[1]);
			dup2(pipecmd->pipefd[0], STDIN_FILENO);
			close(pipecmd->pipefd[0]);
			run_cmd(pipecmd->right, shell);// RECURSAO LADO DIREITO PIPE
			free_cmd(cmd);
			exit(0);
		}
		close(pipecmd->pipefd[0]);
		close(pipecmd->pipefd[1]);
		wait(NULL);
		wait(NULL);
	}
}



