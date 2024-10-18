/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_free_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:18:57 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/17 13:08:44 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_redirections(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = NULL;
		redir = next;
	}
}

void	free_execcmd(t_execcmd *cmd)
{
	t_execcmd	*ecmd;

	if (!cmd)
		return;
	ecmd = (t_execcmd *)cmd;
	free_redirections(ecmd->redir);
	free(cmd);
	return;
}

void free_cmd(t_cmd *cmd)
{
	t_execcmd *execcmd;
	t_pipecmd *pipecmd;

	if (cmd == NULL)
		return;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		if (execcmd->redir)
			free_redirections(execcmd->redir);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		free_cmd(pipecmd->left);
		free_cmd(pipecmd->right);
	}
	free(cmd);
	cmd = NULL;
}
