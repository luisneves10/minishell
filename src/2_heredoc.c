/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/31 16:02:08 by daduarte         ###   ########.fr       */
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

static void	read_heredoc(t_heredoc *cur)
{
	char	*line;
	//int		fd;
	//char	delimiter[50];
	//free heredoc
	//passar fd e delimiter para variavel
	signal(SIGINT, heredoc_sig_handler);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line) // EOF = CTRL + D // DAR ERRO QUE APARECE NO BASH
		{
			printf("minishell: heredocument delimited by end-of-file (wanted %s)\n", cur->delimiter);
			break ;
		}
		if (*line
			&& !ft_strncmp(line, cur->delimiter, ft_strlen(cur->delimiter)))
		{
			free(line);
			break ;
		}
		write(cur->fd, line, ft_strlen(line));
		write(cur->fd, "\n", 1);
		free(line);
		line = NULL;
	}
	exit(0);
}

int	process_heredoc(t_heredoc *curr)
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
	{
		signal(SIGINT, SIG_DFL);
		read_heredoc(curr);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
		{
			signal(SIGINT, SIG_DFL);
			return (1);
		}
	}
	return (0);
}


int	handle_heredoc(t_shell *shell)
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
		curr->fd = open(curr->filepath, O_WRONLY | O_CREAT | O_EXCL, 0644);
		if (curr->fd < 0)
		{
			perror("open error (heredoc)");
			return (-1);
		}
		if (process_heredoc(curr) == 1)
		{
			close(curr->fd);
			return (1);
		}
		close(curr->fd);
		curr = curr->next;
	}
	return (0);
}
