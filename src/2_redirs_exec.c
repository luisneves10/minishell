/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redirs_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:45:59 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/23 10:17:35 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_in(t_fds *fds)
{
	if (fds->saved_in == -1)
		fds->saved_in = dup(STDIN_FILENO);  // GUARDAR O STDIN ORIGINAL
	if (fds->saved_in < 0)
	{
		perror("dup error (saving original stdout)");
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
		fds->saved_out = dup(STDOUT_FILENO); // GUARDAR O STDOUT ORIGINAL
	if (fds->saved_out < 0)
	{
		perror("dup error (saving original stdout)");
		exit(1);
	}
	if (dup2(fds->out_fd, STDOUT_FILENO) < 0 || fds->saved_out < 0)
	{
		perror("dup2 error (output redirection)");
		exit(1);
	}
}

int	redirs_conditions(t_fds *fds, t_redir *redir)
{
	if (redir->type == '<')
	{
		fds->in_fd = open(redir->file, O_RDONLY);
		if (fds->in_fd < 0)
		{
			perror("open error (input redirection)");
			return (-1); //tirei daqui o exit
		}
		handle_in(fds);
	}
	if (redir->type == '>')
	{
		fds->out_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds->out_fd < 0)
		{
			perror("open error (output redirection)");
			return (-1);
		}
		handle_out(fds);
	}
	if (redir->type == '+')
	{
		fds->out_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds->out_fd < 0)
		{
			perror("open error (append redirection)");
			return (-1);
		}
		handle_out(fds);
	}
	return (1);
}

t_fds	*init_fds(void)
{
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	fds->in_fd = -1;
	fds->out_fd = -1;
	fds->saved_in = -1;
	fds->saved_out = -1;
	return (fds);
}

void	handle_redirs(t_execcmd *execcmd, t_shell *shell)
{
	t_redir	*redir;
	t_fds	*fds;

	fds = init_fds();
	redir = execcmd->redir;
	while (redir)
	{
		if (redirs_conditions(fds, redir) < 0)
			return ;
		redir = redir->next;
	}
	if (execcmd->argv[0])
		execute_commands(execcmd, shell);
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
	if (fds->out_fd != -1)
		close(fds->out_fd);// FECHAR OUTPUT FD
	if (fds->in_fd != -1)
		close(fds->in_fd);// FECHAR INPUT FD
	free(fds);
}
