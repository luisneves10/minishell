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

static char	*clean_single_quotes(char quote_type, char *tok)
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
	while (tok[i] && tok[i] != quote_type)
		tmp[j++] = tok[i++];
	if (tok[i] && tok[i] == quote_type)
		i++;
	while (tok[i] && tok[i] != quote_type)
		tmp[j++] = tok[i++];
	if (tok[i] && tok[i] == quote_type)
		i++;
	while (tok[i])
		tmp[j++] = tok[i++];
	tok2 = ft_strdup(tmp);
	free (tmp);
	free (tok);
	return (tok2);
}

static char	*clean_double_quotes(char quote_type, char *tok)
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
	while (tok[i] && tok[i] != quote_type)
		tmp[j++] = tok[i++];
	if (tok[i] && tok[i] == quote_type)
		i++;
	while (tok[i] && tok[i] != quote_type)
		tmp[j++] = tok[i++];
	if (tok[i] && tok[i] == quote_type)
		i++;
	while (tok[i])
		tmp[j++] = tok[i++];
	tok2 = ft_strdup(tmp);
	free (tmp);
	free (tok);
	return (tok2);
}

char	*final_token(char *tok, t_shell *shell)
{
	char	*tok2;
	char	quote_type;
	int		i;

	tok2 = NULL;
	if (!ft_strchr(tok, '"') && !ft_strchr(tok, '\''))
	{
		// DEAL EXPANSOES !!!
		return (tok);
	}
	i = 0;
	while (tok[i] && tok[i] != '"' && tok[i] != '\'')
		i++;
	quote_type = tok[i];
	if (quote_type == '"')
	{
		tok2 = clean_double_quotes(quote_type, tok);
		return (final_token(tok2, shell));
	}
	else if (quote_type == '\'')
	{
		tok2 = clean_single_quotes(quote_type, tok);
		return (final_token(tok2, shell));
	}
	return (tok2);
}
