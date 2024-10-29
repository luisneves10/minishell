/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/29 11:52:29 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*get_delimiter(char *start_tok, char *end_tok, t_shell *shell)
{
	int			len;
	t_heredoc	*new_heredoc;
	t_heredoc	*current;

	current = NULL;
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

static void	read_heredoc(t_heredoc *current)
{
	char	*line;

	line = NULL;
	while (1)
		{
			line = readline("> ");
			if (!line)
			{
				perror("readline error");
				break;
			}
			if (*line 
				&& ft_strncmp(line, current->delimiter, ft_strlen(line)) == 0)
			{
				free(line);
				break;
			}
			write(current->fd, line, ft_strlen(line));
			write(current->fd, "\n", 1);
			free(line);
			line = NULL;
		}
}

void	handle_heredoc(t_shell *shell)
{
	t_heredoc	*current;
	char	*index;

	shell->heredoc_head = shell->heredoc;
	current = shell->heredoc;
	while (current)
	{
		index = ft_itoa(current->index);
		current->filepath = ft_strjoin("../heredoc_", index);
		free(index);
		current->fd = open(current->filepath, O_WRONLY | O_CREAT | O_EXCL, 0644);
		if (current->fd < 0)
		{
			perror("open error (heredoc)");
			return ;
		}
		read_heredoc(current);
		close(current->fd);
		current = current->next;
	}
}
