/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipe_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/01 12:15:48 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	child1_process(t_pipecmd *pipecmd, char *envp[])
{
	char	*path;
	t_execcmd *left;
	t_execcmd *right;

	left = (t_execcmd *)pipecmd->left;
	right = (t_execcmd *)pipecmd->right;
	path = get_cmd_path(envp, left->argv[0]);
	dup2(pipecmd->pipefd[1], STDOUT_FILENO);
	close(pipecmd->pipefd[1]);
	close(pipecmd->pipefd[0]);
	if (execve(path, left->argv, envp) == -1)
	{
		perror("execvp command1");
		exit(0);
	}
}

void	child2_process(t_pipecmd *pipecmd, char *envp[])
{
	char	*path;
	t_execcmd *left;
	t_execcmd *right;

	left = (t_execcmd *)pipecmd->left;
	right = (t_execcmd *)pipecmd->right;
	path = get_cmd_path(envp, right->argv[0]);
	dup2(pipecmd->pipefd[0], STDIN_FILENO);
	close(pipecmd->pipefd[1]);
	close(pipecmd->pipefd[0]);
	if (execve(path, right->argv, envp) == -1)
	{
		perror("execvp command2");
		exit(0);
	}
} */

void	child1_process(t_pipecmd *pipecmd, char *envp[], int prev_pipe)
{
	//if there is previous pipe, read from it
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	//the current process writes on the pipe's write end
	dup2(pipecmd->pipefd[1], STDOUT_FILENO);
	close(pipecmd->pipefd[0]);
	close(pipecmd->pipefd[1]);
	t_execcmd *left = (t_execcmd *)pipecmd->left;
	char *path = get_cmd_path(envp, left->argv[0]);
	if (execve(path, left->argv, envp) == -1)
	{
		perror("execve error");
		exit(1);
	}
}

void	final_cmd(t_cmd *curr_cmd, char *envp[], int prev_pipe)
{
	t_execcmd	*execcmd = (t_execcmd *)curr_cmd;
	int	pid;

	printf("cmd: %s\n", execcmd->argv[0]);
	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid == 0)
	{
		//if there is previous pipe, read from it
		if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
		//Execute the last command
		char *path = get_cmd_path(envp, execcmd->argv[0]);
		if (execve(path, execcmd->argv, envp) == -1)
		{
			perror("execve error");
			exit(1);
		}
		if (prev_pipe != -1)
		close(prev_pipe);
	}
}

void	fork_function(t_pipecmd *pipecmd, char *envp[])
{
	t_cmd	*curr_cmd;
	int	prev_pipe;
	prev_pipe = -1;
	curr_cmd = (t_cmd *)pipecmd;
	while (curr_cmd->type == PIPE)
	{
		if (pipe(pipecmd->pipefd) == -1)
			perror("pipe error");
		pipecmd->pid1 = fork();
		if (pipecmd->pid1 == -1)
			perror("fork error");
		else if (pipecmd->pid1 == 0)
			child1_process(pipecmd, envp, prev_pipe);
		else
		{
			close(pipecmd->pipefd[1]);
			if (prev_pipe != -1)
				close(prev_pipe);
			prev_pipe = pipecmd->pipefd[0];
			curr_cmd = pipecmd->right;
		}
	}
	final_cmd(curr_cmd, envp, prev_pipe);
	wait(NULL);
	wait(NULL);
}

/* void	fork_function(t_pipecmd *pipecmd, char *envp[])
{
	pipecmd->pid1 = fork();
	if (pipecmd->pid1 < 0)
		printf("error fork");
	if (pipecmd->pid1 == 0)
		child1_process(pipecmd, envp);
	pipecmd->pid2 = fork();
	if (pipecmd->pid2 < 0)
		printf("error fork");
	if (pipecmd->pid2 == 0)
		child2_process(pipecmd, envp);
} */

void	close_all(t_pipecmd *pipecmd)
{
	close(pipecmd->pipefd[0]);
	close(pipecmd->pipefd[1]);
	waitpid(pipecmd->pid1, NULL, 0);
	waitpid(pipecmd->pid2, NULL, 0);
}
