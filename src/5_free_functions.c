/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_free_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:18:57 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/04 16:46:14 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_heredocs(t_shell *shell, int flag)
{
	t_heredoc	*current;
	t_heredoc	*temp;

	current = shell->heredoc_head;
	while (current != NULL)
	{
		if (current->fd >= 0)
			close (current->fd);
		if (flag == 1)
		{
			if (current->filepath)
				if (access(current->filepath, F_OK) == 0)
					if (unlink(current->filepath) < 0)
						perror("Error deleting heredoc file");
			shell->heredoc = NULL;
			shell->heredoc_head = NULL;
		}
		if (current->filepath)
		{
			free(current->filepath);
			current->filepath = NULL;
		}
		if (current->delimiter)
		{
			free(current->delimiter);
			current->delimiter = NULL;
		}
		temp = current;
		current = current->next;
		free(temp);
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
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;
	int			i;

	if (cmd == NULL)
		return ;
	i = 0;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		if (execcmd->redir)
			free_redirections(execcmd->redir);
		while (execcmd->argv[i])
			free (execcmd->argv[i++]);
		free (execcmd->argv);
		free (execcmd);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		free_cmd(pipecmd->left);
		free_cmd(pipecmd->right);
		free (pipecmd);
	}
	cmd = NULL;
}
