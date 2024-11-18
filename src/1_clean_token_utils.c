/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_clean_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:16:29 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/18 15:13:46 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	final_token_size(t_chunk *chunks)
{
	int	i;

	i = 0;
	while (chunks && chunks->str)
	{
		i += ft_strlen(chunks->str);
		chunks = chunks->next;
	}
	return (i);
}

t_chunk	*chunk_last(t_chunk *chunk)
{
	if (!chunk || !chunk->str)
		return (NULL);
	while (chunk && chunk->str)
	{
		if (chunk->next)
			chunk = chunk->next;
		else
			break ;
	}
	return (chunk);
}

void	chunk_add_back(t_chunk **chunks, t_chunk *chunk, t_chunk **head)
{
	t_chunk	*last;

	last = chunk_last(*chunks);
	if (!last)
	{
		*chunks = chunk;
		*head = chunk;
	}
	else
		last->next = chunk;
}

void	free_chunks(t_chunk *chunks)
{
	t_chunk	*tmp;

	while (chunks)
	{
		tmp = chunks->next;
		free (chunks->str);
		free (chunks);
		chunks = tmp;
	}
}

char	*chunks_join(t_chunk *chunks, t_shell *shell)
{
	char	*str;

	str = ft_calloc(sizeof(char), final_token_size(chunks) + 1);
	if (!str)
		return (NULL);
	while (chunks && chunks->str)
	{
		if (ft_strncmp(chunks->str, EXPAND_NULL, 1) == 0
			&& ft_strlen(chunks->str) == ft_strlen(EXPAND_NULL))
		{
			shell->ambiguous = 1;
			str = ft_strjoin_free(str, "");
		}
		else if (chunks->type == '$' && chunks->next)
			str = ft_strjoin_free(str, "");
		else
			str = ft_strjoin_free(str, chunks->str);
		chunks = chunks->next;
	}
	return (str);
}
