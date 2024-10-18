/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_constructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:24:29 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/17 11:26:13 by daduarte         ###   ########.fr       */
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
	ft_memset(cmd->argv, 0, (sizeof(char *) * 20));
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

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(0); // DAR HANDLE
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
	shell->name = argv[0] + 2;
	shell->exit_status = 0;
	shell->prompt = NULL;
	shell->input = NULL;
	shell->env = copy_env(envp);
	if (!shell->env)
		return (NULL);
	return (shell);
}
