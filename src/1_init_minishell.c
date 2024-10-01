/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/01 11:00:21 by luibarbo         ###   ########.fr       */
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
		print_user_and_cwd();
		input = readline("$\033[0m ");
		if (!input)
		{
			printf("exit\n");
			free (input);
			free_env(local_env);
			break ;
		}
		if (*input)
		{
			add_history(input);
			runcmd(parsecmd(input), local_env);
		}
		free (input);
	}
}
