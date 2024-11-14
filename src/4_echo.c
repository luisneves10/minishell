/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:35:17 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/14 11:55:28 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_echo_flag(char *arg)
{
	if (arg[0] == '-' && arg[1] == 'n' && arg[2] == '\0')
		return (1);
	return (0);
}

int	ft_echo(char **argv)
{
	int	i;

	i = 1;
	if (!argv[1] || (argv[1] && !argv[1][0]))
	{
		printf("\n");
		return (0);
	}
	if (is_echo_flag(argv[1]))
		i++;
	while (argv[i] && argv[i + 1] != NULL)
		printf("%s ", argv[i++]);
	if (is_echo_flag(argv[1]))
	{
		if (argv[i])
			printf("%s", argv[i]);
	}
	else
		printf("%s\n", argv[i]);
	return (0);
}
