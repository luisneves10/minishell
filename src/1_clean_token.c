/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_clean_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:18:22 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/07 12:27:59 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chunk_no_quotes(t_chunk **chunk, char **cpy, int size)
{
	(*chunk)->str = ft_strndup(*cpy, size);
	(*chunk)->type = 'a';
	if (!(*chunk)->str)
		free(*chunk);
}

t_chunk	*init_chunk()
{
	t_chunk	*chunk;

	chunk = malloc(sizeof(t_chunk));
	if (!chunk)
		return (NULL);
	chunk->str = NULL;
	chunk->next = NULL;
	return (chunk);
}

t_chunk	*create_chunk(char **tok, t_shell *shell)
{
	t_chunk	*chunk;
	int		i;
	char	*cpy;

	shell = (void *)shell; // DELETE DELETE DELETE DELETE DELETE
	chunk = init_chunk();
	i = 0;
	cpy = *tok;
	while (cpy[i] && cpy[i] != '"' && cpy[i] != '\'')
	{
		i++;
		(*tok)++;
	}
	if (i > 0)
		chunk_no_quotes(&chunk, &cpy, i);
	else
	{
		chunk->type = **tok;
		while (cpy[i + 1] && cpy[i + 1] != chunk->type)
			i++;
		chunk->str = ft_strndup(cpy + 1, i);
		*tok = cpy + i + 2;
	}
	return (chunk);
}

char	*clean_token(char *tok, t_shell *shell)
{
	t_chunk	*chunks;
	t_chunk	*chunk;
	t_chunk	*head;
	char	*tmp;
	char	*tok_cpy;
	char	*final_token;

	tok_cpy = tok;
	chunks = NULL;
	while (*tok_cpy)
	{
		chunk = create_chunk(&tok_cpy, shell);
		if (!chunk)
		{
			free_chunks(head);
			return (NULL);
		}
		if (chunk->type == '"' || chunk->type == 'a')
		{
			tmp = ft_strdup(chunk->str);
			free (chunk->str);
			chunk->str = NULL;
			chunk->str = deal_expansion(tmp, shell);
			free(tmp);
			tmp = NULL;
		}
		chunk_add_back(&chunks, chunk, &head);
	}
	final_token = chunks_join(chunks);
	free_chunks(head);
	return (final_token);
}
