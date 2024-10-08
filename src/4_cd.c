/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/08 16:12:30 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*
 * $HOME not defined: se executar "cd" --> "bash: cd: HOME not set"
 * $HOME defined : se executar "cd" --> vai para o HOME
 * "cd <arg1> <arg2> <arg3>" --> muda para o caminho definido em <arg1>
 * todos os args a frente do primeiro sao ignorados
 * se o comando for executado com sucesso, $PWD e $OLD_PWD levam update
 */

/* static int	update_pwd(char **local_env, char *var_name, char *var_value)
{
	int		index;
	int		len;
	char	*new_var;

	len = ft_strlen(var_name) + ft_strlen(var_value) + 2;
	index = var_search(local_env, var_name);
	if (index >= 0)
	{
		new_var = malloc(sizeof(char) * len);
		if (!new_var)
			return (1);

	}
	return (0);
} */

int	ft_cd(char **argv, char ***local_env)
{
	char	**env;

	env = *local_env;
	if (has_options(argv, "cd"))
		return (1);
	if (!argv[1])
	{
		// ACRESCENTAR ERRO CASO HOME NAO ESTEJA DEFINID
		chdir(env[var_search(*local_env, "HOME")] + 5);
		return (1);
	}
	else
	{
		if (argv[1][0] == '~')
			argv[1]++;
		if (chdir(argv[1]) == -1)
		{
			perror("minishell: cd");
			return (1);
		}
	}
	return (0);
}
