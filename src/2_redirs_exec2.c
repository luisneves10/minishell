/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:40:32 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/21 14:45:05 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ambigous_redir(t_shell *shell, t_redir *redir)
{
	if (redir && redir->type != '-'
		&& redir->file[0] == '\0' && shell->ambiguous == 1)
	{
		shell->exit_status = 1;
		mini_error("ambiguous redirect", -1, shell);
		close_fds(shell->fds);
		free(shell->fds);
		return (1);
	}
	return (0);
}

int	file_permissions(t_shell *shell, t_redir *redir)
{
	if (redir->type == '>' || redir->type == '+')
	{
		if (access(redir->file, F_OK) == 0
			&& access(redir->file, W_OK) == -1)
		{
			perror("minishell");
			shell->exit_status = 1;
			close_fds(shell->fds);
			free(shell->fds);
			return (1);
		}
	}
	if (redir->type == '<')
	{
		if (access(redir->file, F_OK) == 0
			&& access(redir->file, R_OK) == -1)
		{
			perror("minishell");
			shell->exit_status = 1;
			close_fds(shell->fds);
			free(shell->fds);
			return (1);
		}
	}
	return (0);
}

int	valid_redir(t_shell *shell, t_redir *redir, t_cmd *cmd)
{
	if (redir && (redir->type == '<' || redir->type == '-'))
	{
		if (redirs_in(shell->fds, redir, shell, cmd) < 0)
		{
			close_fds(shell->fds);
			free(shell->fds);
			return (0);
		}
	}
	else if (redir && (redir->type == '>' || redir->type == '+'))
	{
		if (redirs_out(shell->fds, redir, shell) < 0)
		{
			close_fds(shell->fds);
			free(shell->fds);
			return (0);
		}
	}
	return (1);
}
