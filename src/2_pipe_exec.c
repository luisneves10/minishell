/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipe_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/23 12:03:14 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_function1(t_pipecmd *pipecmd, t_shell *shell)
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
		dup2(pipecmd->pipefd[1], STDOUT_FILENO);//lidar com erro?
		close(pipecmd->pipefd[1]);
		run_cmd(pipecmd->left, shell);// RECURSAO LADO ESQUERDO PIPE
		free_cmd((t_cmd *)pipecmd);
		free_shell(shell, 1);
		exit(0);
	}

}

void	fork_function2(t_pipecmd *pipecmd, t_shell *shell)
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
		dup2(pipecmd->pipefd[0], STDIN_FILENO);//lidar com erro?
		close(pipecmd->pipefd[0]);
		run_cmd(pipecmd->right, shell);// RECURSAO LADO DIREITO PIPE
		free_cmd((t_cmd *)pipecmd);
		free_shell(shell, 1);
		exit(0);
	}
}
