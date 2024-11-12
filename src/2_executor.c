/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:37:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/12 16:31:38 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmds_path(char	*path, char	*cmd)
{
	int		i;
	char	*true_cmd;
	char	*full_path;
	char	**directory;

	true_cmd = NULL;
	true_cmd = ft_strjoin("/", cmd);
	directory = ft_split(path, ':');
	if (!directory)
		return (NULL);
	i = -1;
	while (directory[++i])
	{
		full_path = ft_strjoin(directory[i], true_cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(true_cmd);
			free_split(directory);
			return (full_path);
		}
		free(full_path);
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
	if (*cmd == '\0')
		return (NULL);
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

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) == -1)
		return (0);
	if (stat(path, &path_stat) == -1)
	{
		perror("stat error");
		return (0);
	}
	return (S_ISDIR(path_stat.st_mode));
	}

void	command_type(t_cmd *cmd, t_shell *shell, char **path)
{
	if (is_builtin(cmd) != NULL)
	{
		exec_builtin(cmd->argv, is_builtin(cmd), shell);
		*path = NULL;
		return ;
	}
	else if (cmd->argv[0][0] == '/' || ft_strncmp(cmd->argv[0], "./", 2) == 0
		|| ft_strncmp(cmd->argv[0], "../", 3) == 0) //encontrar / no fim da str
		{
			*path = cmd->argv[0];
			if (is_directory(*path))
		{
			mini_error("Is a directory", -1, shell);
			shell->exit_status = 126;
			*path = NULL;
			return ;
		}
		}
	else
	{
		*path = get_cmd_path(shell->env, cmd->argv[0]);
		if (!(*path))
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			shell->exit_status = 127;
			return ;
		}
	}
}

void	execute_commands(t_cmd *cmd, t_shell *shell)
{
	int		pid;
	char	*path;

/* 	if (cmd->argv[0][0] == '\0' || !cmd->argv[0])
	 	return ; */
	command_type(cmd, shell, &path);
	if (path == NULL)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("error fork");
		exit(1);
	}
	if (pid == 0)
		handle_child_process(path, cmd, shell);
	else
		handle_parent_process(pid, path, cmd, shell);
}

void	run_cmd(t_cmd *cmd, t_shell *shell)
{
	int	status1;
	int	status2;
	int	pid1;
	int	pid2;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		handle_redirs(cmd, shell);
	else if (cmd->type == PIPE)
	{
		if (pipe(cmd->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		pid1 = fork_function1(cmd, shell);
		pid2 = fork_function2(cmd, shell);
		close(cmd->pipefd[0]);
		close(cmd->pipefd[1]);
		waitpid(pid1, &status1, 0);
		waitpid(pid2, &status2, 0);
		if (WIFEXITED(status2))
			shell->exit_status = WEXITSTATUS(status2);
		else if (WIFEXITED(status1))
			shell->exit_status = WEXITSTATUS(status1);
		else
			shell->exit_status = 0;
	}
}
