/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/30 15:31:46 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_in(t_fds *fds)
{
	if (fds->saved_in == -1)
		fds->saved_in = dup(STDIN_FILENO);
	if (fds->saved_in < 0)
	{
		perror("dup error (saving original stdin)");
		exit(1);
	}
	if (dup2(fds->in_fd, STDIN_FILENO) < 0 || fds->saved_in < 0)
	{
		perror("dup2 error (input redirection)");
		exit(1);
	}
}

static void	handle_out(t_fds *fds)
{
	if (fds->saved_out == -1)
		fds->saved_out = dup(STDOUT_FILENO);
	if (fds->saved_out < 0)
	{
		perror("dup error (saving original stdout)");
		exit(1);
	}
	if (dup2(fds->out, STDOUT_FILENO) < 0 || fds->saved_out < 0)
	{
		perror("dup2 error (output redirection)");
		exit(1);
	}
}

int	redirs_conditions(t_fds *fds, t_redir *redir, t_shell *shell)
{
	if (redir && (redir->type == '<' || redir->type == '-'))
	{
		if (redir->type == '-')
		{
			redir->file = shell->heredoc->filepath;
			shell->heredoc = shell->heredoc->next;
		}
		if (fds->in_fd != -1)
			close(fds->in_fd);
		fds->in_fd = open(redir->file, O_RDONLY);
		if (fds->in_fd < 0)
			return (mini_error("open error (input redirection)", -1));
		handle_in(fds);
	}
	else if (redir && (redir->type == '>' || redir->type == '+'))
	{
		if (fds->out != -1)
			close(fds->out);
		if (redir->type == '+')
			fds->out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fds->out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds->out < 0)
			return (mini_error("open error (output redirection)", -1));
		handle_out(fds);
	}
	return (1);
}

void	close_fds(t_fds *fds)
{
	if (fds->saved_in != -1)
	{
		dup2(fds->saved_in, STDIN_FILENO);
		close(fds->saved_in);
	}
	if (fds->saved_out != -1)
	{
		dup2(fds->saved_out, STDOUT_FILENO);
		close(fds->saved_out);
	}
	if (fds->out != -1)
		close(fds->out);
	if (fds->in_fd != -1)
		close(fds->in_fd);
}

void	handle_redirs(t_execcmd *execcmd, t_shell *shell)
{
	t_redir	*redir;
	t_fds	*fds;

	fds = init_fds();
	redir = execcmd->redir;
	while (redir)
	{
		if (redirs_conditions(fds, redir, shell) < 0)
			return ;
		redir = redir->next;
	}
	if (execcmd->argv[0])
		execute_commands(execcmd, shell);
	close_fds(fds);
	free(fds);
}
