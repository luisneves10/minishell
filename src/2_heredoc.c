/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/13 12:01:19 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc_cases(char *line, char *delimiter, int fd)
{
	if (fd < 0)
	{
		perror("open error (heredoc)");
		return (1);
	}
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

static void	read_heredoc(char *delimiter, char *file)
{
	int		fd;
	int		ret;
	char	*line;

	signal(SIGINT, heredoc_sig_handler);
	line = NULL;
	ret = 0;
	while (1)
	{
		line = readline("> ");
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ret = read_heredoc_cases(line, delimiter, fd);
		if (ret == 2)
			break ;
		else if (ret == 1)
			return ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		close(fd);
	}
	exit(0);
}

void	child_process_heredoc(t_heredoc *curr, t_shell *shell)
{
	char	delimiter[4096];
	char	file[4096];

	signal(SIGINT, SIG_DFL);
	strcpy(delimiter, curr->delimiter);//mudar strcpy
	strcpy(file, curr->filepath);//mudar strcpy
	delete_heredocs(shell, 0);
	free_cmd(shell->head);
	free_shell(shell, 2);
	read_heredoc(delimiter, file);
	exit(0);
}

int	process_heredoc(t_heredoc *curr, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return (-1);
	}
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
		signal(SIGINT, SIG_DFL);
	}
	return (0);
}

int	handle_heredoc(t_shell *shell)
{
	char		*index;
	t_heredoc	*curr;

	if (shell->heredoc_flag != 1)
		return (0);
	shell->heredoc_head = shell->heredoc;
	curr = shell->heredoc;
	while (curr)
	{
		index = ft_itoa(curr->index);
		curr->filepath = ft_strjoin("/tmp/heredoc_", index);
		free(index);
		if (process_heredoc(curr, shell) == 1)
		{
			shell->exit_status = 130;
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}
