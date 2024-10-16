/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/16 09:46:04 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(char *envp[])
{
	char	*input;
	char	**local_env;

	local_env = copy_env(envp);
	signals();
	while (1)
	{
		input = readline("\033[1;34mminishell$\033[0m ");
		if (!input)
		{
			printf("exit\n");
			free (input);
			free_env(local_env);
			break ;
		}
		if (syntax_check(input) == 0)
		{
			if (*input)
			{
				add_history(input);
				run_cmd(parse_cmd(input), &local_env);
			}
		}
		free (input);
	}
}
