/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipe_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/20 11:24:46 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child1_process(t_pipecmd *pipecmd, char **local_env)
{
	char	*path;
	t_execcmd *left;
	// t_execcmd *right;

	left = (t_execcmd *)pipecmd->left;
	// right = (t_execcmd *)pipecmd->right;
	path = get_cmd_path(local_env, left->argv[0]);
	dup2(pipecmd->pipefd[1], STDOUT_FILENO);
	close(pipecmd->pipefd[1]);
	close(pipecmd->pipefd[0]);
	if (execve(path, left->argv, local_env) == -1)
	{
		perror("execvp command1");
		exit(0);
	}
}

void	child2_process(t_pipecmd *pipecmd, char **local_env)
{
	char	*path;
	// t_execcmd *left;
	t_execcmd *right;

	// left = (t_execcmd *)pipecmd->left;
	right = (t_execcmd *)pipecmd->right;
	path = get_cmd_path(local_env, right->argv[0]);
	dup2(pipecmd->pipefd[0], STDIN_FILENO);
	close(pipecmd->pipefd[1]);
	close(pipecmd->pipefd[0]);
	if (execve(path, right->argv, local_env) == -1)
	{
		perror("execvp command2");
		exit(0);
	}
}

void	fork_function(t_pipecmd *pipecmd, char **local_env)
{
	pipecmd->pid1 = fork();
	if (pipecmd->pid1 < 0)
		printf("error fork");
	if (pipecmd->pid1 == 0)
		child1_process(pipecmd, local_env);
	pipecmd->pid2 = fork();
	if (pipecmd->pid2 < 0)
		printf("error fork");
	if (pipecmd->pid2 == 0)
		child2_process(pipecmd, local_env);
}

void	close_all(t_pipecmd *pipecmd)
{
	close(pipecmd->pipefd[0]);
	close(pipecmd->pipefd[1]);
	waitpid(pipecmd->pid1, NULL, 0);
	waitpid(pipecmd->pid2, NULL, 0);
}
