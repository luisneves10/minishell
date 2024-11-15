/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipe_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/15 15:44:41 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	run_cmd(cmd, shell);
	delete_heredocs(shell, 0);
	free_cmd(shell->head);
	exit_status = shell->exit_status;
	free_shell(shell, 2);
	exit(exit_status);
}

int	fork_function1(t_cmd *pipecmd, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGINT, child_signal_handler);
		signal(SIGQUIT, SIG_DFL);
		close(pipecmd->pipefd[0]);
		if (dup2(pipecmd->pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 error");
			exit(-1);
		}
		close(pipecmd->pipefd[1]);
		fork_exit(pipecmd->left, shell);
	}
	return (pid);
}

int	fork_function2(t_cmd *pipecmd, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGINT, child_signal_handler);
		signal(SIGQUIT, SIG_DFL);
		close(pipecmd->pipefd[1]);
		if (dup2(pipecmd->pipefd[0], STDIN_FILENO) < 0)
		{
			perror("dup2 error");
			exit(-1);
		}
		close(pipecmd->pipefd[0]);
		fork_exit(pipecmd->right, shell);
	}
	return (pid);
}
