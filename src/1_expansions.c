/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expansions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:12:34 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/07 10:33:37 by daduarte         ###   ########.fr       */
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

char	*is_expansion(char *token, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*expand;

	tmp = token;
	expand = NULL;
	if (*token == '$')
	{
		token++;
		if (*token == '?' && *(token + 1) == '\0') //acrescentar condicoes
		{
			if (g_ctrlc == 1)
				shell->exit_status = 130;
			return (ft_itoa(shell->exit_status));
		}
		expand = create_expand(token);
		i = 0;
		while (shell->env[i])
		{
			if (var_search(shell->env, expand) >= 0)
				return (free(expand), ft_strdup(shell->env[i]
						+ (var_name_len(shell->env[i]) + 1)));
			else
				return (free(expand), ft_strdup(""));
			i ++;
		}
	}
	return (ft_strdup(tmp));
}
