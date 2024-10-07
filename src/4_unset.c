/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:42:31 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/03 15:59:52 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_options(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			printf("unset: No options are allowed.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static char	**remove_var(char **local_env, char *var)
{
	int	i;
	int	var_size;

	var_size = 0;
	while (var[var_size])
		var_size++;
	i = 0;
	while (local_env[i])
	{
		if (ft_strncmp(local_env[i], var, var_size) == 0
			&& local_env[i][var_size] == '=')
		{
			free (local_env[i]);
			local_env[i] = ft_strdup(local_env[env_size(local_env)]);
			free (local_env[env_size(local_env)]);
			return (local_env);
		}
		i++;
	}
	return (local_env);
}

void	ft_unset(char **argv, char ***local_env)
{
	int	i;

	if (!argv[1])
		return ;
	if (has_options(argv))
		return ;
	i = 1;
	while (argv[i] != NULL)
	{
		*local_env = remove_var(*local_env, argv[i]);
		i++;
	}
}
