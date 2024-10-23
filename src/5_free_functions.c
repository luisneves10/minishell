/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_free_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:18:57 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/22 16:20:11 by daduarte         ###   ########.fr       */
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

/* void free_cmd(t_cmd *cmd)
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
} */
void free_cmd(t_cmd *cmd)
{
    t_execcmd   *exec_cmd;
    t_pipecmd   *pipe_cmd;

    if (!cmd)
        return;

    if (cmd->type == EXEC)
    {
        exec_cmd = (t_execcmd *)cmd;

        // Free redir structure if it's allocated
        if (exec_cmd->redir)
        {
            free(exec_cmd->redir);
            exec_cmd->redir = NULL;
        }

        // Free the command structure itself
        free(exec_cmd);
    }
    else if (cmd->type == PIPE)
    {
        pipe_cmd = (t_pipecmd *)cmd;

        // Free left and right commands in the pipe
        if (pipe_cmd->left)
        {
            free_cmd(pipe_cmd->left);
            pipe_cmd->left = NULL;
        }
        if (pipe_cmd->right)
        {
            free_cmd(pipe_cmd->right);
            pipe_cmd->right = NULL;
        }

        // Free the pipe command structure
        free(pipe_cmd);
    }
}
