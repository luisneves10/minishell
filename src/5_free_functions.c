/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_free_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:18:57 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/16 10:31:27 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_execcmd(t_execcmd *cmd)
{
	//int i = 0;

	if (!cmd)
		return;
	//while (cmd->argv[i])
	//{
	//	free(cmd->argv[i]);
	//	i++;
	//}
	//free(cmd);
	return;
}

void	free_pipecmd(t_pipecmd *cmd)
{
	if (!cmd)
		return;
	free_cmd(cmd->left);
	free_cmd(cmd->right);
	//free(cmd);
}
void	free_redircmd(t_redircmd *cmd)
{
	if (!cmd)
		return;
	free_cmd(cmd->cmd);
	//free(cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->type == EXEC)
		free_execcmd((t_execcmd *)cmd);
	else if (cmd->type == PIPE)
		free_pipecmd((t_pipecmd *)cmd);
	else if (cmd->type == REDIR)
		free_redircmd((t_redircmd *)cmd);
	free(cmd);
}
