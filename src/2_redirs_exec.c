/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/15 22:46:50 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_redirs(t_redircmd *redircmd, int in_out_flag)
{
	if (in_out_flag == 0)
	{
		redircmd->fd = open(redircmd->file, O_RDONLY);
		if (redircmd->fd < 0)
		{
			perror("redir");
			return;
		}
		dup2(redircmd->fd, STDIN_FILENO);
		close(redircmd->fd);
	}
	else
	{
		redircmd->fd = open(redircmd->file, redircmd->mode, 0644);
		if (redircmd->fd < 0)
		{
			perror("redir");
			return;
		}
		dup2(redircmd->fd, STDOUT_FILENO);
		close(redircmd->fd);
	}
}

void	redirect_cmd(t_redircmd *redircmd, char ***local_env)
{
	t_execcmd *execcmd;
	int saved_fd_in;
	int saved_fd_out;

	saved_fd_in = dup(STDIN_FILENO);
	saved_fd_out = dup(STDOUT_FILENO);
	if (redircmd->mode & O_WRONLY)
		handle_redirs(redircmd, 1);
	else
		handle_redirs(redircmd, 0);
	execcmd = (t_execcmd *)redircmd->cmd;
	nulterminate((t_cmd *)execcmd);
	execute_commands(execcmd, local_env);
	dup2(saved_fd_out, STDOUT_FILENO);
	dup2(saved_fd_in, STDIN_FILENO);
	close(saved_fd_in);
	close(saved_fd_out);
}