/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/30 13:00:47 by daduarte         ###   ########.fr       */
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

static void	read_heredoc(t_heredoc *cur)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perror("readline error");
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
}

void	handle_heredoc(t_shell *shell)
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
			return ;
		}
		read_heredoc(curr);
		close(curr->fd);
		curr = curr->next;
	}
}
