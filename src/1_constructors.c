/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_constructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:24:29 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/20 15:40:15 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	ft_memset(cmd, 0, sizeof(t_execcmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
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

t_cmd	*redircmd(t_cmd	*next_cmd, t_token *tok, int mode, int fd)
{
	t_redircmd	*cmd;
	//t_execcmd	*execcmd;

	//execcmd = (t_execcmd *)next_cmd;
	cmd = malloc(sizeof(t_redircmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	ft_memset(cmd, 0, sizeof(t_redircmd));
	cmd->type = REDIR;
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
