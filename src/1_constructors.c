/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_constructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:24:29 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/19 10:24:46 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*execcmd(void)
{
	struct execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	if (!cmd)
		exit(0);
	memset(cmd, 0, sizeof(t_execcmd));
	cmd->type = EXEC;
	return ((t_cmd*)cmd);
}

t_cmd	*pipecmd(t_cmd	*left, t_cmd	*right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(t_cmd*));
	memset(cmd, 0, sizeof(t_cmd*));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd*)cmd);
}
