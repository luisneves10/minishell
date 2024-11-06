/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expansions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:12:34 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/06 16:02:02 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		expand = token;
		i = 0;
		while (shell->env[i])
		{
			if (ft_strncmp(shell->env[i], expand, ft_strlen(expand)) == 0)
				return (ft_strdup(shell->env[i]
						+ (var_name_len(shell->env[i]) + 1)));
			i ++;
		}
	}
	return (tmp);
}
