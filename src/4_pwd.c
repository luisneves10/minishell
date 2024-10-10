/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/10 12:31:23 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * pwd works even with additional arguments in front
 * it does not work if you attempt to use any flag but -LP
 * For example, if you write "pwd -a", it prints:
 * "bash: pwd: (flag): invalid option"
 * Subject says to build pwd with no options, but how should we handle the
 * additional arguments?
 * */

int	ft_pwd(char **argv)
{
	char	path[1024];

	if (argv[1] && argv[1][0] == '-')
	{
		printf("minishell: pwd: %s: invalid option\n", argv[1]);
		return (-1);
	}
	getcwd(path, sizeof(path));
	printf("%s\n", path);
	return (0);
}
