/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/20 15:08:22 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(char *envp[])
{
	char	*input;

	signals();
	while (1)
	{
		print_user_and_cwd();
		input = readline("$\033[0m ");
		if (!input)
		{
			printf("exit\n");
			free (input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			runcmd(parsecmd(input), envp);
		}
		free (input);
	}
}
