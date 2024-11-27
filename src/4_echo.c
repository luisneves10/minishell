/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:35:17 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/18 14:31:28 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_echo_flag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	if (!arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (is_echo_flag(argv[i]))
		i++;
	while (argv[i] && argv[i + 1] != NULL)
	{
		ft_putstr_fd(argv[i++], 1);
		ft_putchar_fd(' ', 1);
	}
	if (is_echo_flag(argv[1]))
	{
		if (argv[i])
			ft_putstr_fd(argv[i], 1);
	}
	else
		ft_putendl_fd(argv[i], 1);
	return (0);
}
