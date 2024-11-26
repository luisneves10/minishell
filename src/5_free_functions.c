/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_free_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:18:57 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/26 11:25:37 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_herefile(t_heredoc *current)
{
	if (current->filepath)
		if (access(current->filepath, F_OK) == 0)
			if (unlink(current->filepath) < 0)
				perror("Error deleting heredoc file");
}

static void	delete_delimiter(int flag, t_heredoc *heredoc)
{
	if (flag == 1)
		delete_herefile(heredoc);
	if (heredoc->filepath)
	{
		free(heredoc->filepath);
		heredoc->filepath = NULL;
	}
	if (heredoc->delimiter)
	{
		free(heredoc->delimiter);
		heredoc->delimiter = NULL;
	}
}

void	delete_heredocs(t_shell *shell, int flag, t_cmd *cmd)
{
	t_heredoc	*current;
	t_heredoc	*temp;
	t_cmd		*curr;

	if (!cmd)
		return ;
	curr = cmd;
	if (curr->type == EXEC)
	{
		current = curr->heredoc_head;
		while (current != NULL)
		{
			if (current->fd >= 0)
				close (current->fd);
			delete_delimiter(flag, current);
			temp = current;
			current = current->next;
			free(temp);
		}
	}
	else if (curr->type == PIPE)
	{
		delete_heredocs(shell, flag, curr->left);
		delete_heredocs(shell, flag, curr->right);
	}
}

void	free_redirections(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->type != '-')
			free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	i = 0;
	if (cmd->type == EXEC)
	{
		if (cmd->redir)
			free_redirections(cmd->redir);
		while (cmd->argv[i])
			free (cmd->argv[i++]);
		free (cmd->argv);
		free (cmd);
	}
	else if (cmd->type == PIPE)
	{
		free_cmd(cmd->left);
		free_cmd(cmd->right);
		free (cmd);
	}
	cmd = NULL;
}
