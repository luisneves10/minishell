/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/16 16:03:20 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_out(t_redircmd *redircmd, int flag)
{
	redircmd->fd = open(redircmd->file, redircmd->mode, 0644);
	if (redircmd->fd < 0)
	{
		perror("redir");
		return;
	}
	if (flag == 1)
		return ;
	dup2(redircmd->fd, STDOUT_FILENO);
	close(redircmd->fd);
}

static void handle_in(t_redircmd *redircmd, int flag)
{
	redircmd->fd = open(redircmd->file, O_RDONLY);
	if (redircmd->fd < 0)
	{
		perror("redir");
		return;
	}
	if (flag == 1)
		return ;
	dup2(redircmd->fd, STDIN_FILENO);
	close(redircmd->fd);
}

void	redirect_cmd(t_redircmd *redircmd, t_shell *shell)
{
	t_execcmd	*execcmd;
	int			flag;
	int			saved_fd_in;
	int			saved_fd_out;

	flag = 0;
	saved_fd_in = dup(STDIN_FILENO);
	saved_fd_out = dup(STDOUT_FILENO);
	//printf("command: %s\n", ((t_execcmd *)redircmd->cmd)->argv[0]);
	if (((t_execcmd *)redircmd->cmd)->argv[0] == NULL)
		flag = 1;
	if (redircmd->mode & O_WRONLY)
		handle_out(redircmd, flag);
	else
		handle_in(redircmd, flag);
	//SE NAO HOUVER COMANDO NAO EXECUTA
	execcmd = (t_execcmd *)redircmd->cmd;
	//null_terminate((t_cmd *)execcmd);
	if (((t_execcmd *)redircmd->cmd)->argv[0] == NULL)
		return ;
	execute_commands(execcmd, shell);
	dup2(saved_fd_out, STDOUT_FILENO);
	dup2(saved_fd_in, STDIN_FILENO);
	close(saved_fd_in);
	close(saved_fd_out);
}
