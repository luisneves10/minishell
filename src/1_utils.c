/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:19:00 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/23 15:40:09 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_count(char *input, t_shell *shell)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			shell->argc++;
			i++;
		}
		if (input[i] && input[i] != ' ')
			shell->argc++;
		if (input[i] == '"' || input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '"' && input[i] != '\'')
				i++;
			i++;
		}
		while (input[i] && input[i] != ' ')
			i++;
	}
}
