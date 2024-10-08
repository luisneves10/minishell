/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:21:52 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/08 15:49:50 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_update(char **local_env, char *var)
{
	int	i;
	int	var_size;

	var_size = 0;
	while (var[var_size] && var[var_size] != '=')
		var_size++;
	i = 0;
	while (local_env[i])
	{
		if (ft_strncmp(local_env[i], var, var_size) == 0)
		{
			free (local_env[i]);
			local_env[i] = NULL;
			local_env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

static char	**update_env(char **local_env, char *var)
{
	int		i;
	int		local_env_size;
	char	**new_env;

	if (var_update(local_env, var))
		return (local_env);
	local_env_size = env_size(local_env);
	new_env = malloc((local_env_size + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (local_env[i])
	{
		new_env[i] = ft_strdup(local_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free_env(local_env);
	return (new_env);
}

int	ft_export(char **argv, char ***local_env)
{
	int	i;

	if (argv[1] == NULL)
	{
		ft_export_no_args(*local_env);
		return (0);
	}
	if (has_options(argv, argv[0]))
		return (1);
	i = 1;
	while (argv[i] != NULL)
	{
		*local_env = update_env(*local_env, argv[i]);
		i++;
	}
	return (0);
}
