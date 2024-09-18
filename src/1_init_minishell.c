/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/18 12:03:18 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(void)
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
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free (input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			printf("Input: %s\n", input); // placeholder para o parse do input
		}
		free (input);
	}
}
