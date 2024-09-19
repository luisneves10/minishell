/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/19 12:48:52 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * */

int	ft_cd(char *args)
{
	if (!args)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else
	{
		if (chdir(args) == -1)
		{
			printf("%s: no such directory\n", args);
			return (-1);
		}
	}
	return (0);
}
