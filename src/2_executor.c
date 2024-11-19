/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:37:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/19 10:32:48 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_slash(char *arg)
{
	if (ft_strlen(arg) == 0)
		return (0);
	if (arg[0] == '/' || ft_strncmp(arg, "./", 2) == 0
		|| ft_strncmp(arg, "../", 3) == 0
		|| arg[ft_strlen(arg) - 1] == '/')
		return (1);
	return (0);
}

static void	command_type(t_cmd *cmd, t_shell *shell, char **path)
{
	if (is_builtin(cmd) != NULL)
	{
		exec_builtin(cmd->argv, is_builtin(cmd), shell);
		*path = NULL;
		return ;
	}
	else if (has_slash(cmd->argv[0]))
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
			return (path_errors(shell, cmd));
	}
}

void	execute_commands(t_cmd *cmd, t_shell *shell)
{
	int		pid;
	char	*path;

	signal(SIGINT, SIG_IGN);
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

static void	get_exit_status(t_shell *shell)
{
	if (WIFEXITED(shell->status2))
		shell->exit_status = WEXITSTATUS(shell->status2);
	else if (WIFEXITED(shell->status1))
		shell->exit_status = WEXITSTATUS(shell->status1);
	else
		shell->exit_status = 0;
}

void	run_cmd(t_cmd *cmd, t_shell *shell)
{
	int	pid1;
	int	pid2;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		handle_redirs(cmd, shell);
	else if (cmd->type == PIPE)
	{
		signal(SIGINT, SIG_IGN);
		if (pipe(cmd->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		pid1 = fork_function1(cmd, shell);
		pid2 = fork_function2(cmd, shell);
		wait_pipes_close(cmd, shell, pid1, pid2);
		get_exit_status(shell);
	}
	signals();
}
