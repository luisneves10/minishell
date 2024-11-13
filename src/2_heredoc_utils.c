/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:29:45 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/13 11:58:25 by daduarte         ###   ########.fr       */
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
	char		*tmp;
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
	tmp = ft_calloc((end_tok - start_tok) + 1, sizeof(char));
	if (!tmp)
	{
		free(new_heredoc);
		perror("calloc error");
		return (NULL);
	}
	ft_strlcpy(tmp, start_tok, (end_tok - start_tok) + 1);
	new_heredoc->delimiter = clean_token(tmp, shell, HEREDOC);
	free(tmp);
	return (get_heredoc(shell, new_heredoc));
}

void	close_fds(t_fds *fds)
{
	if (fds->saved_in != -1)
	{
		dup2(fds->saved_in, STDIN_FILENO);
		close(fds->saved_in);
	}
	if (fds->saved_out != -1)
	{
		dup2(fds->saved_out, STDOUT_FILENO);
		close(fds->saved_out);
	}
	if (fds->out != -1)
		close(fds->out);
	if (fds->in_fd != -1)
		close(fds->in_fd);
}
