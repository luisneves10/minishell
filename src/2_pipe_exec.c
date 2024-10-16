/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipe_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/16 11:16:31 by daduarte         ###   ########.fr       */
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

void handle_redirection(t_redircmd *redircmd, char ***local_env, int prev_pipe)
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	redirect_cmd(redircmd, local_env);
}

void execute_final_cmd(t_execcmd *execcmd, char ***local_env, int prev_pipe)
{
	int		pid;
	char	*path;

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
		path = get_cmd_path(*local_env, execcmd->argv[0]);
		if (execve(path, execcmd->argv, *local_env) == -1)
		{
			perror("execve error");
			exit(1);
		}
	}
	close(prev_pipe);
	wait(NULL);
}

void final_cmd(t_cmd *curr_cmd, char ***local_env, int prev_pipe)
{
	if (curr_cmd->type == REDIR)
	{
		t_redircmd *redircmd = (t_redircmd *)curr_cmd;
		int pid = fork();
		if (pid == 0)
		{
			handle_redirection(redircmd, local_env, prev_pipe);
			exit(0);
		}
		close(prev_pipe);
		wait(NULL);
	}
	else if (curr_cmd->type == EXEC)
	{
		t_execcmd *execcmd = (t_execcmd *)curr_cmd;
		execute_final_cmd(execcmd, local_env, prev_pipe);
	}
	else
		printf("Unknown command type\n");
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
	int	prev_pipe;
	int		pipefd[2];
	prev_pipe = -1;
	int		pid;
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
