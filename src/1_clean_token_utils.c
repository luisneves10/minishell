/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_clean_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:16:29 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/06 13:42:14 by luibarbo         ###   ########.fr       */
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
