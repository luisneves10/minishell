/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/04 15:07:55 by daduarte         ###   ########.fr       */
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
		if (!input || ft_strncmp(input, "exit", 4) == 0)
		{
			printf("exit\n");
			free (input);
			break ;
		}
		syntax_check(input);
		if (*input)
		{
			add_history(input);
			runcmd(parsecmd(input), envp);
		}
		free (input);
	}
}
