/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:34:48 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/13 15:35:24 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_redirs(char **str)
{
	if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			return ('+');
		}
		(*str)--;
		return ('>');
	}
	else if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			return ('-');
		}
		(*str)--;
		return ('<');
	}
	return ('?');
}

char	*aloc_file(char *start_file, t_redir *new_redir,
	char *end_file, t_shell *shell)
{
	int		file_length;
	char	*file;
	char	*temp;

	file_length = end_file - start_file;
	temp = ft_strndup(start_file, file_length);
	file = clean_token(temp, shell, TOKEN);
	if (!file)
	{
		free(new_redir);
		free(temp);
		exit(1);
	}
	free(temp);
	return (file);
}

t_redir	*add_redir(t_redir *head, int type, t_token *tok, t_shell *shell)
{
	t_redir	*tmp;
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		exit(1);
	memset(new_redir, 0, sizeof(t_redir));
	new_redir->type = type;
	if (type == '-')
		new_redir->file = NULL;
	else
		new_redir->file = aloc_file(tok->start, new_redir, tok->end, shell);
	new_redir->next = NULL;
	if (!head)
		return (new_redir);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	return (head);
}
