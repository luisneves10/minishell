/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:36:02 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/14 15:55:16 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void	handle_child_process(char *path, t_cmd *execcmd, t_shell *shell)
{
	execve(path, execcmd->argv, shell->env);
	perror("execve error");
	if (access(path, F_OK) == -1)
		exit(127);
	exit(126);
}

void	handle_parent_process(int pid, char *path,
							t_cmd *execcmd, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
	if (path != execcmd->argv[0])
		free(path);
}
