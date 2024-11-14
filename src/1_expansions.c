/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expansions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:12:34 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/14 13:09:49 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_expansion(char **token, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*expand;

	tmp = *token;
	expand = NULL;
	if (**token == '$')
	{
		(*token)++;
		if (is_whitespace(**token) || **token == '\0')
			return (ft_strdup("$"));
		if (**token == '0' || **token == '$'
			|| ft_isdigit(**token) || **token == '?')
			return (expand_cases(token, shell));
		expand = create_expand(*token);
		*token = *token + ft_strlen(expand);
		i = var_search(shell->env, expand);
		if (i >= 0)
			return (free(expand), ft_strdup(shell->env[i]
					+ (var_name_len(shell->env[i]) + 1)));
		else
		{
			//shell->expand_flag = 1;
			//return (free(expand), ft_strdup(EXPAND_NULL));
			return (free(expand), ft_strdup(EXPAND_NULL));
		}
	}
	return (ft_strdup(tmp));
}

char	*deal_expansion(char *token, t_shell *shell)
{
	int		i;
	char	*final;
	char	*tmp;

	tmp = NULL;
	final = ft_calloc(sizeof(char), 1);
	while (*token)
	{
		if (*token && *token == '$')
		{
			tmp = is_expansion(&token, shell);
			final = ft_strjoin_free(final, tmp);
			free(tmp);
			tmp = NULL;
		}
		else
		{
			i = 0;
			final = expansion_join(token, final, &i);
			token = token + i;
		}
	}
	return (final);
}
