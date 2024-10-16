/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/16 12:27:36 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_out(t_redircmd *redircmd)
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

static void handle_in(t_redircmd *redircmd)
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

void	redirect_cmd(t_redircmd *redircmd, t_shell *shell)
{
	t_execcmd *execcmd;
	int saved_fd_in;
	int saved_fd_out;

	saved_fd_in = dup(STDIN_FILENO);
	saved_fd_out = dup(STDOUT_FILENO);
	if (redircmd->mode & O_WRONLY)
		handle_out(redircmd);
	else
		handle_in(redircmd);
	//SE NAO HOUVER COMANDO NAO EXECUTA
	if (((t_execcmd *)redircmd->cmd)->argv[0] == NULL)
		return ;
	execcmd = (t_execcmd *)redircmd->cmd;
	null_terminate((t_cmd *)execcmd);
	execute_commands(execcmd, shell);
	dup2(saved_fd_out, STDOUT_FILENO);
	dup2(saved_fd_in, STDIN_FILENO);
	close(saved_fd_in);
	close(saved_fd_out);
}
