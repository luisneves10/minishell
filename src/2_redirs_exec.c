/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/21 15:16:33 by daduarte         ###   ########.fr       */
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

int	redirs_in(t_fds *fds, t_redir *redir, t_shell *shell, t_cmd *cmd)
{
	if (redir->type == '-')
	{
		redir->file = cmd->heredoc->filepath;
		cmd->heredoc = cmd->heredoc->next;
	}
	if (fds->in_fd != -1)
		close(fds->in_fd);
	fds->in_fd = open(redir->file, O_RDONLY);
	if (fds->in_fd < 0)
		return (mini_error("No such file or directory", -1, shell));
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
		return (mini_error("No such file or directory", -1, shell));
	handle_out(fds);
	return (1);
}

void	handle_redirs(t_cmd *execcmd, t_shell *shell)
{
	t_redir	*redir;

	shell->fds = init_fds();
	redir = execcmd->redir;
	if (ambigous_redir(shell, redir))
		return ;
	while (redir)
	{
		if (file_permissions(shell, redir))
			return ;
		else if (!valid_redir(shell, redir, execcmd))
			return ;
		redir = redir->next;
	}
	if (execcmd->argv[0])
		execute_commands(execcmd, shell);
	close_fds(shell->fds);
	free(shell->fds);
	shell->fds = NULL;
}
