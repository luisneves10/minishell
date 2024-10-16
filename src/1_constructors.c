/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_constructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:24:29 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/16 09:45:07 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*exec_cmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	ft_memset(cmd, 0, sizeof(t_execcmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(t_pipecmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	ft_memset(cmd, 0, sizeof(t_pipecmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*redir_cmd(t_cmd	*next_cmd, t_token *tok, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(t_redircmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	ft_memset(cmd, 0, sizeof(t_redircmd));
	cmd->type = REDIR;
	if (next_cmd == NULL)
		cmd->cmd = NULL;
	else
		cmd->cmd = next_cmd;
	cmd->file = tok->start;
	cmd->end_file = tok->end;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(0); // DAR HANDLE
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}
