/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/05 13:15:31 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_in(t_fds *fds)
{
	if (fds->saved_in == -1)
		fds->saved_in = dup(STDIN_FILENO);
	if (fds->saved_in < 0)
	{
		perror("dup error (saving original stdin)\n");
		exit(1);
	}
	if (dup2(fds->in_fd, STDIN_FILENO) < 0 || fds->saved_in < 0)
	{
		perror("dup2 error (input redirection)\n");
		exit(1);
	}
}

static void	handle_out(t_fds *fds)
{
	if (fds->saved_out == -1)
		fds->saved_out = dup(STDOUT_FILENO);
	if (fds->saved_out < 0)
	{
		perror("dup error (saving original stdout)\n");
		exit(1);
	}
	if (dup2(fds->out, STDOUT_FILENO) < 0 || fds->saved_out < 0)
	{
		perror("dup2 error (output redirection)\n");
		exit(1);
	}
}

int	redirs_in(t_fds *fds, t_redir *redir, t_shell *shell)
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
		return (mini_error("No such file or directory\n", -1, shell));
	handle_in(fds);
	return (1);
}

int	redirs_out(t_fds *fds, t_redir *redir, t_shell *shell)
{
	if (fds->out != -1)
		close(fds->out);
	if (redir->type == '+')
		fds->out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fds->out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->out < 0)
		return (mini_error("No such file or directory\n", -1, shell));
	handle_out(fds);
	return (1);
}

void	handle_redirs(t_execcmd *execcmd, t_shell *shell)
{
	t_redir	*redir;
	t_fds	*fds;

	fds = init_fds();
	redir = execcmd->redir;
	while (redir)
	{
		if (redir && (redir->type == '<' || redir->type == '-'))
		{
			if (redirs_in(fds, redir, shell) < 0)
				return ;
		}
		else if (redir && (redir->type == '>' || redir->type == '+'))
			if (redirs_out(fds, redir, shell) < 0)
				return ;
		redir = redir->next;
	}
	if (execcmd->argv[0])
		execute_commands(execcmd, shell);
	close_fds(fds);
	free(fds);
}
