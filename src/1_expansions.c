/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expansions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:12:34 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/07 13:07:15 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_expand(char *expand)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (expand[i] && (ft_isalnum(expand[i]) || expand[i] == '_'))
		i ++;
	str = ft_strndup(expand, i);
	return (str);
}

/* char	*return_exit_code(char *token, t_shell *shell)
{
	char	*final_token;

	final_token = NULL;
	if (*token == '?')
	{
		final_token = create_expand(token);
		if (ft_strncmp(final_token, "?", 1) == 0)
			return(free(final_token), ft_itoa(shell->exit_status));
	}
} */

char	*is_expansion(char **token, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*final;
	char	*expand;

	tmp = *token;
	expand = NULL;
	final = NULL;
	if (**token == '$')
	{
		(*token)++;
		if (**token == '?' && **(token + 1) == '\0') //acrescentar condicoes
		{
			if (g_ctrlc == 1)
				shell->exit_status = 130;
			return (ft_itoa(shell->exit_status));
		}
		expand = create_expand(*token);
		*token = *token + ft_strlen(expand);
		i = var_search(shell->env, expand);
		if (i >= 0)
			return (free(expand), ft_strdup(shell->env[i]
					+ (var_name_len(shell->env[i]) + 1)));
		else
			return (free(expand), ft_strdup(""));
	}
	return (ft_strdup(tmp));
}

char	*deal_expansion(char *token, t_shell *shell)
{
	int		i;
	char	*final;
	char	*tmp;
	char	*tmp2;

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
			while (token[i] && token[i] != '$')
				i++;
			tmp2 = ft_strndup(token, i);
			final = ft_strjoin_free(final, tmp2);
			free(tmp2);
			tmp2 = NULL;
			token = token + i;
		}
	}
	return (final);
}
