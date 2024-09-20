/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_constructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:24:29 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/19 16:58:50 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*execcmd(void)
{
	struct execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	memset(cmd, 0, sizeof(t_execcmd));
	cmd->type = EXEC;
	return ((t_cmd*)cmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(t_pipecmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	memset(cmd, 0, sizeof(t_pipecmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd*)cmd);
}

t_cmd	*redircmd(t_cmd	*next_cmd, char *file, char *end_file, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(t_redircmd));
	if (!cmd)
		exit(0); // DAR HANDLE
	memset(cmd, 0, sizeof(t_redircmd));
	cmd->type = REDIR;
	cmd->cmd = next_cmd;
	cmd->file = file;
	cmd->end_file = end_file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}
