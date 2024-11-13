/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/13 11:55:42 by daduarte         ###   ########.fr       */
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
	if (redir && redir->type != '-' && ft_strncmp(redir->file, EXPAND_NULL, 11) == 0)
	{
		shell->exit_status = 1;
		mini_error("ambiguous redirect", -1, shell);
		close_fds(shell->fds);
		free(shell->fds);
		return;
	}
	while (redir)
	{
		if (redir->type == '>' || redir->type == '+')
		{
			if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) == -1)
			{
				perror("minishell");
				shell->exit_status = 1;
				close_fds(shell->fds);
				free(shell->fds);
				return;
			}
		}
		if (redir->type == '<')
		{
			if (access(redir->file, F_OK) == 0 && access(redir->file, R_OK) == -1)
			{
				perror("minishell");
				shell->exit_status = 1;
				close_fds(shell->fds);
				free(shell->fds);
				return;
			}
		}
		if (redir && (redir->type == '<' || redir->type == '-'))
		{
			if (redirs_in(shell->fds, redir, shell) < 0)
			{
				close_fds(shell->fds);
				free(shell->fds);
				return ;
			}
		}
		else if (redir && (redir->type == '>' || redir->type == '+'))
			if (redirs_out(shell->fds, redir, shell) < 0)
			{
				close_fds(shell->fds);
				free(shell->fds);
				return ;
			}
		redir = redir->next;
	}
	if (execcmd->argv[0])
		execute_commands(execcmd, shell);
	close_fds(shell->fds);
	free(shell->fds);
	shell->fds = NULL;
}
