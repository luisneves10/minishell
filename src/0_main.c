/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:58:12 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/17 11:03:46 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*input;

	signals();
	if (argc != 1 || argv[1])
		return (0);
	while (1)
	{
		input = readline("\033[1;34mminishell$\033[0m ");
		if (!input || ft_strncmp(input, "exit", 5) == 0)
		{
			free (input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			printf("Input: %s\n", input);
		}
		free (input);
	}
	return (0);
}
