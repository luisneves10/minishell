/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_clean_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:18:22 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/06 13:38:36 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

t_chunk	*create_chunk(char **tok, t_shell *shell)
{
	t_chunk	*chunk;
	int		i;
	char	*cpy;

	shell = (void *)shell; // DELETE DELETE DELETE DELETE DELETE
	i = 0;
	cpy = *tok;
	chunk = malloc(sizeof(t_chunk));
	if (!chunk)
		return (NULL);
	chunk->next = NULL;
	while (cpy[i] && cpy[i] != '"' && cpy[i] != '\'')
	{
		i++;
		(*tok)++;
	}
	if (i > 0)
	{
		chunk->str = ft_strndup(cpy, i);
		chunk->type = 'a';
	}
	else
	{
		chunk->type = **tok;
		(*tok)++;
		while (cpy[i + 1] && cpy[i + 1] != chunk->type)
			i++;
		chunk->str = ft_strndup(*tok, i);
		*tok = cpy + i + 2;
	}
	return (chunk);
}

char	*clean_token(char *tok, t_shell *shell)
{
	t_chunk	*chunks;
	t_chunk	*chunk;
	char	*tok_cpy;
	char	*final_token;

	tok_cpy = tok;
	chunks = malloc(sizeof(t_chunk));
	if (!chunks)
		return (NULL);
	chunks->str = NULL;
	chunks->next = NULL;
	while (*tok_cpy)
	{
		chunk = create_chunk(&tok_cpy, shell);
		chunk_add_back(&chunks, chunk->str, chunk->type);
	}
	final_token = ft_calloc(sizeof(char), final_token_size(chunks));
	if (!final_token)
		return (NULL);
	while (chunks && chunks->str)
	{
		final_token = ft_strjoin_free(final_token, chunks->str);
		chunks = chunks->next;
	}
	return (final_token);
}
