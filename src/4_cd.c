/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/10 15:29:57 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

/*
 * $HOME not defined: se executar "cd" --> "bash: cd: HOME not set"
 * $HOME defined : se executar "cd" --> vai para o HOME
 * "cd <arg1> <arg2> <arg3>" --> muda para o caminho definido em <arg1>
 * todos os args a frente do primeiro sao ignorados
 * se o comando for executado com sucesso, $PWD e $OLD_PWD levam update
 */

static int	home_is_set(char **local_env)
{
	int	index;

	index = var_search(local_env, "HOME");
	if (index >= 0)
		if (ft_strchr(local_env[index], '='))
			return (1);
	printf("minishell: cd: HOME not set\n");
	return (0);
}

static int	update_var(char **local_env, char *var_name, char *var_value)
{
	int		index;
	int		len;
	char	*new_var;

	len = ft_strlen(var_name) + ft_strlen(var_value) + 2;
	index = var_search(local_env, var_name);
	if (index >= 0)
	{
		new_var = ft_calloc(sizeof(char), len);
		if (!new_var)
			return (1);
		new_var[len] = '\0';
		new_var = ft_strjoin_free(new_var, var_name);
		new_var = ft_strjoin_free(new_var, "=");
		new_var = ft_strjoin_free(new_var, var_value);
		free (local_env[index]);
		local_env[index] = new_var;
	}
	return (0);
}

int	ft_cd(char **argv, char ***local_env)
{
	char	**env;
	char	path[1024];

	env = *local_env;
	if (has_options(argv, "cd"))
		return (1);
	if (!argv[1])
	{
		if (home_is_set(*local_env))
			chdir(env[var_search(*local_env, "HOME")] + 5);
		return (0);
	}
	else
	{
		// TRATAR DO PATH ~
		// TRATAR DO PATH ~
		// TRATAR DO PATH ~
		// if (argv[1][0] == '~')
		// 	argv[1]++;
		if (chdir(argv[1]) == -1)
		{
			perror("minishell: cd");
			return (1);
		}
		update_var(*local_env, "OLDPWD", env[var_search(*local_env, "PWD")] + 4);
		update_var(*local_env, "PWD", getcwd(path, sizeof(path)));
	}
	return (0);
}
