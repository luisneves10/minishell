/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipe_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/10 13:18:43 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child1_process(t_pipecmd *pipecmd, char ***local_env, int prev_pipe, int *pi)
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	dup2(pi[1], STDOUT_FILENO);
	close(pi[0]);
	close(pi[1]);
	t_execcmd *left = (t_execcmd *)pipecmd->left;
	execute_commands(left, local_env);
}

void	final_cmd(t_cmd *curr_cmd, char ***local_env, int prev_pipe)
{
	t_execcmd	*execcmd;
	int			pid;

	execcmd = (t_execcmd *)curr_cmd;
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
		execute_commands(execcmd, local_env);
		if (prev_pipe != -1)
			close(prev_pipe);
		exit (0);
	}
}

void	fork_loop(t_cmd **curr_cmd, int *pipefd, int *pid, int *prev_pipe, char ***local_env)
{
	t_pipecmd *pipecmd;

	pipecmd = (t_pipecmd *)*curr_cmd;
	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		exit(0);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork error");
		exit(0);
	}
	if (*pid == 0)
	{
		child1_process(pipecmd, local_env, *prev_pipe, pipefd);
		exit(1);
	}
	else
	{
		close(pipefd[1]);
		if (*prev_pipe != -1)
			close(*prev_pipe);
		*prev_pipe = pipefd[0];
		*curr_cmd = pipecmd->right;
	}
}

void	fork_function(t_pipecmd *pipecmd, char ***local_env)
{
	t_cmd	*curr_cmd;
	int		prev_pipe;
	int		pipefd[2];
	int		pid;

	prev_pipe = -1;
	curr_cmd = (t_cmd *)pipecmd;
	while (curr_cmd->type == PIPE)
		fork_loop(&curr_cmd, pipefd, &pid, &prev_pipe, local_env);
	final_cmd(curr_cmd, local_env, prev_pipe);
	while (wait(NULL) > 0);
}

void	close_all(t_pipecmd *pipecmd)
{
	close(pipecmd->pipefd[0]);
	close(pipecmd->pipefd[1]);
	waitpid(pipecmd->pid1, NULL, 0);
	waitpid(pipecmd->pid2, NULL, 0);
}
