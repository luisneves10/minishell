/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:36:02 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/18 16:19:14 by daduarte         ###   ########.fr       */
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
	int		flag;
	char	*tmp;

	flag = 0;
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, SIG_DFL);
	execve(path, execcmd->argv, shell->env);
	perror("execve error");
	if (access(path, F_OK) == -1)
	{
		tmp = ft_strjoin("/", execcmd->argv[0]);
		if (ft_strncmp(path, tmp, ft_strlen(path)) == 0)
			free(path);
		free(tmp);
		flag = 1;
	}
	free_shell(shell, EXIT_CMD);
	if (flag == 1)
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
