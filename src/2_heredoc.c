/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/28 22:39:59 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc_cases(char *line, char *delimiter, int fd)
{
	if (!line)
	{
		printf("minishell: heredocument delimited by ");
		printf("end-of-file (wanted %s)\n", delimiter);
		close(fd);
		return (2);
	}
	if (*line && ft_strlen(delimiter) == ft_strlen(line)
		&& !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		free(line);
		close(fd);
		return (2);
	}
	return (0);
}

static void	read_heredoc(char *delimiter, int write_fd)
{
	int		ret;
	char	*line;

	signal(SIGINT, heredoc_sig_handler);
	line = NULL;
	ret = 0;
	while (1)
	{
		line = readline("> ");
		ret = read_heredoc_cases(line, delimiter, write_fd);
		if (ret == 2)
			break ;
		else if (ret == 1)
			return ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
		line = NULL;
	}
	close(write_fd);
	exit(0);
}

void	child_process_heredoc(t_heredoc *curr, t_shell *shell)
{
	char	delimiter[4096];
	int		fd;

	fd = curr->pipe_fd[1];
	signal(SIGINT, SIG_DFL);
	ft_strlcpy(delimiter, curr->delimiter, ft_strlen(curr->delimiter) + 1);
	delete_heredocs(shell, 2, shell->head);
	free_cmd(shell->head);
	free_shell(shell, 2);
	read_heredoc(delimiter, fd);
	exit(0);
}

int	process_heredoc(t_heredoc *curr, t_shell *shell)
{
	pid_t	pid;
	int		status;

	curr->fd = curr->pipe_fd[0];
	pid = fork();
	if (pid == -1)
		return (perror("fork error"), -1);
	else if (pid == 0)
		child_process_heredoc(curr, shell);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
		{
			signal(SIGINT, signal_handler);
			return (1);
		}
		close(curr->pipe_fd[1]);
		signal(SIGINT, SIG_DFL);
	}
	return (0);
}

int	handle_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_heredoc	*curr;

	if (!cmd)
		return (1);
	else if (cmd->type == EXEC)
	{
		if (shell->heredoc_flag != 1)
			return (0);
		cmd->heredoc_head = cmd->heredoc;
		curr = cmd->heredoc;
		if (heredoc_loop(curr, shell) == 1)
			return (1);
	}
	else if (cmd->type == PIPE)
	{
		handle_heredoc(cmd->left, shell);
		handle_heredoc(cmd->right, shell);
	}
	return (0);
}
