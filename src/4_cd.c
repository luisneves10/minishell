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
 * $HOME not defined: se executar "cd" --> "bash: cd: HOME not set"
 * $HOME defined : se executar "cd" --> vai para o HOME
 * "cd <arg1> <arg2> <arg3>" --> muda para o caminho definido em <arg1>
 * todos os args a frente do primeiro sao ignorados
 * se o comando for executado com sucesso, $PWD e $OLD_PWD levam update
 */

int	ft_cd(char **argv, char **local_env)
{
	if (!argv[1])
	{
		// chdir();
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
