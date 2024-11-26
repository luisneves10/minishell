/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:29:45 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/26 11:23:15 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_loop(t_heredoc *curr, t_shell *shell)
{
	static int	real_index;
	char		*index;

	while (curr)
	{
		index = ft_itoa(real_index++);
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

t_heredoc	*get_heredoc(t_heredoc *new_heredoc, t_cmd *cmd)
{
	t_heredoc	*current;

	current = NULL;
	if (cmd->heredoc == NULL)
	{
		new_heredoc->index = 0;
		cmd->heredoc = new_heredoc;
		cmd->heredoc_head = new_heredoc;
	}
	else
	{
		current = cmd->heredoc;
		while (current->next != NULL)
			current = current->next;
		new_heredoc->index = current->index + 1;
		current->next = new_heredoc;
	}
	return (cmd->heredoc);
}

t_heredoc	*get_delimiter(char *start_tok, char *end_tok,
			t_shell *shell, t_cmd *cmd)
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
		return (NULL);
	}
	ft_strlcpy(tmp, start_tok, (end_tok - start_tok) + 1);
	if (ft_strchr(tmp, '"') || ft_strchr(tmp, '\''))
		new_heredoc->delimiter = clean_token(tmp, shell, HEREDOC);
	else
		new_heredoc->delimiter = ft_strdup(tmp);
	return (free(tmp), get_heredoc(new_heredoc, cmd));
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
