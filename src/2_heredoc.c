/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/28 17:35:42 by daduarte         ###   ########.fr       */
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
	new_heredoc->next = NULL;
	len = end_tok - start_tok;
	new_heredoc->delimiter = ft_calloc(len + 1, sizeof(char));
	if (!new_heredoc->delimiter)
	{
		free(new_heredoc);
		perror("calloc error");
		return (NULL);
	}
	if (!new_heredoc->delimiter)
		return (NULL);
	ft_strlcpy(new_heredoc->delimiter, start_tok, len + 1);
	new_heredoc->index = 0;
	if (shell->heredoc == NULL)
		shell->heredoc = new_heredoc;
	else
	{
		current = shell->heredoc;
		while (current->next != NULL)
			current = current->next;
		current->next = new_heredoc;
		new_heredoc->index += 1;
	}
	return (shell->heredoc);
}

static void	read_heredoc(t_heredoc *current)
{
	char	*line;

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
		}
}

void	handle_heredoc(t_shell *shell)
{
	t_heredoc	*current;
	char	*index;

	shell->heredoc_head = shell->heredoc;
	//mkdir("../heredocs", 0755);
	current = shell->heredoc;
	while (current)
	{
		index = ft_itoa(current->index);
		current->filepath = ft_strjoin("../heredoc_", index);
		current->fd = open(current->filepath, O_WRONLY | O_CREAT | O_EXCL, 0644);
		if (current->fd < 0)
		{
			perror("open error (heredoc)");
			return ;
		}
		read_heredoc(current);
		close(current->fd);
		current = current->next;
		free(index);
	}
}
