/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/02 11:42:14 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * */

int	ft_cd(char **argv)
{
	if (!argv[1])
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else
	{
		if (argv[1][0] == '~')
			argv[1]++;
		if (chdir(argv[1]) == -1)
		{
			printf("%s: no such directory\n", argv[1]);
			return (-1);
		}
	}
	return (0);
}
