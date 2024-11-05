/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_clean_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:18:22 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/04 14:37:34 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	*clean_quotes(char quote_type, char **tok)
{
	char	*tmp;
	char	*tok2;
	int		i;
	int		j;

	tmp = ft_calloc(sizeof(char), 1000);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	if (**tok && **tok == quote_type)
		i++;
	while (**tok && **tok != quote_type)
		tmp[j++] = tok[i++];
	if (**tok && **tok == quote_type)
		i++;
	tok2 = ft_strdup(tmp);
	free (tmp);
	free (tok);
	return (tok2);
} */

void	free_chunk(t_chunk *chunk)
{
	free (chunk->str);
	chunk->str = NULL;
	chunk->next = NULL;
	free (chunk);
}

t_chunk	*chunk_last(t_chunk *chunk)
{
	if (chunk == NULL)
		return (NULL);
	while (chunk->next)
		chunk = chunk->next;
	return (chunk);
}

void	chunk_add_back(t_chunk **chunk, char *str, char type)
{
	t_chunk	*new;
	t_chunk	*last;

	last = chunk_last(*chunk);
	new = malloc(sizeof(t_chunk));
	if (!new)
		return ;
	if (!last)
		*chunk = new;
	else
		last->next = new;
	new->str = str;
	new->type = type;
	new->next = NULL;
}

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
		while (cpy[i + 1]  && cpy[i + 1] != chunk->type)
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
	final_token = NULL;
	chunks = malloc(sizeof(t_chunk));
	if (!chunks)
		return (NULL);
	while (*tok_cpy)
	{
		chunk = create_chunk(&tok_cpy, shell);
		chunk_add_back(&chunks, chunk->str, chunk->type);
		free_chunk(chunk);
	}
	while (chunks && chunks->str)
	{
		printf("chunks: %s\n", chunks->str); // DELETE DELETE DELETE
		final_token = ft_strjoin_free(final_token, chunks->str);
		chunks = chunks->next;
	}
	printf("---------------------------\n"); // DELETE DELETE DELETE
	printf("| FINAL: %s\n", final_token);    // DELETE DELETE DELETE
	printf("---------------------------\n"); // DELETE DELETE DELETE
	return (final_token);
}
