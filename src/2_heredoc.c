/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/04 16:41:48 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*get_heredoc(t_shell *shell, t_heredoc *new_heredoc)
{
	t_heredoc	*current;

	current = NULL;
	if (shell->heredoc == NULL)
	{
		new_heredoc->index = 0;
		shell->heredoc = new_heredoc;
	}
	else
	{
		current = shell->heredoc;
		while (current->next != NULL)
			current = current->next;
		new_heredoc->index = current->index + 1;
		current->next = new_heredoc;
	}
	return (shell->heredoc);
}

t_heredoc	*get_delimiter(char *start_tok, char *end_tok, t_shell *shell)
{
	int			len;
	t_heredoc	*new_heredoc;

	new_heredoc = malloc(sizeof(t_heredoc));
	if (!new_heredoc)
	{
		perror("malloc error");
		exit(1);
	}
	new_heredoc->delimiter = NULL;
	new_heredoc->filepath = NULL;
	new_heredoc->next = NULL;
	new_heredoc->fd = -1;
	len = end_tok - start_tok;
	new_heredoc->delimiter = ft_calloc(len + 1, sizeof(char));
	if (!new_heredoc->delimiter)
	{
		free(new_heredoc);
		perror("calloc error");
		return (NULL);
	}
	ft_strlcpy(new_heredoc->delimiter, start_tok, len + 1);
	return (get_heredoc(shell, new_heredoc));
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(2);
	}
}

static void	read_heredoc(char *delimiter, char *file)
{
	int		fd;
	char	*line;

	signal(SIGINT, heredoc_sig_handler);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open error (heredoc)");
			return ;
		}
		if (!line)
		{
			printf("minishell: heredocument delimited by end-of-file (wanted %s)\n", delimiter);
			close(fd);
			break ;
		}
		if (*line && ft_strlen(delimiter) == ft_strlen(line)
			&& !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			close(fd);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		close(fd);
	}
	exit(0);
}

int	process_heredoc(t_heredoc *curr, t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		fd;
	char	delimiter[4096];
	char	file[4096];

	fd = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return (-1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		strcpy(delimiter, curr->delimiter);//mudar strcpy
		strcpy(file, curr->filepath);//mudar strcpy
		delete_heredocs(shell, 0);
		free_shell(shell, 2);
		free_cmd(cmd);
		read_heredoc(delimiter, file);
		exit(0);
	}
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


int	handle_heredoc(t_shell *shell, t_cmd *cmd)
{
	char		*index;
	t_heredoc	*curr;

	shell->heredoc_head = shell->heredoc;
	curr = shell->heredoc;
	while (curr)
	{
		index = ft_itoa(curr->index);
		curr->filepath = ft_strjoin("../heredoc_", index);
		free(index);
		if (process_heredoc(curr, shell, cmd) == 1)
		{
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}
