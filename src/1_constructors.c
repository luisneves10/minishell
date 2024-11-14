/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_constructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:24:29 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/14 14:51:32 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_shell *shell, int type, t_cmd *left, t_cmd *right)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit(0);
	ft_memset(cmd, 0, sizeof(t_cmd));
	if (type == EXEC)
	{
		cmd->argv = ft_calloc(sizeof(char *), (shell->argc + 1));
		if (!cmd->argv)
			return (NULL);
	}
	cmd->argc = 0;
	cmd->left = left;
	cmd->right = right;
	cmd->type = type;
	return (cmd);
}

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(0);
	ft_memset(token, 0, sizeof(t_token));
	token->argc = 0;
	return (token);
}

t_shell	*init_struct(char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->head = NULL;
	shell->ambiguous = 0;
	shell->heredoc_flag = 0;
	shell->exit_heredoc = 0;
	shell->heredoc = NULL;
	shell->heredoc_head = NULL;
	shell->name = argv[0] + 2;
	shell->exit_status = 0;
	shell->argc = 0;
	shell->status1 = 0;
	shell->status2 = 0;
	shell->prompt = NULL;
	shell->input = NULL;
	shell->fds = NULL;
	shell->env = copy_env(envp);
	if (!shell->env)
		return (NULL);
	return (shell);
}

t_fds	*init_fds(void)
{
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	fds->in_fd = -1;
	fds->out = -1;
	fds->saved_in = -1;
	fds->saved_out = -1;
	return (fds);
}
