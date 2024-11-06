/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipe_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/06 10:08:31 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_function1(t_cmd *pipecmd, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(77);
	}
	if (pid == 0)
	{
		close(pipecmd->pipefd[0]);
		if (dup2(pipecmd->pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 error");
			exit(-1);
		}
		close(pipecmd->pipefd[1]);
		run_cmd(pipecmd->left, shell);
		delete_heredocs(shell, 0);
		free_cmd(shell->head);
		free_shell(shell, 2);
		exit(0);
	}
}

void	fork_function2(t_cmd *pipecmd, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(77);
	}
	if (pid == 0)
	{
		close(pipecmd->pipefd[1]);
		if (dup2(pipecmd->pipefd[0], STDIN_FILENO) < 0)
		{
			perror("dup2 error");
			exit(-1);
		}
		close(pipecmd->pipefd[0]);
		run_cmd(pipecmd->right, shell);
		free_cmd(shell->head);
		delete_heredocs(shell, 0);
		free_shell(shell, 2);
		exit(0);
	}
}
