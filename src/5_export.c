/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:21:52 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/01 12:52:29 by luibarbo         ###   ########.fr       */
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
			printf("export: No options are allowed.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	var_name_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

static char	**var_update(char **local_env, char *var)
{
	int	i;
	int	var_name_size;

	i = 0;
	while (local_env[i])
	{
		var_name_size = var_name_len(var);
		if (ft_strncmp(local_env[i], var, var_name_size + 1) == 0)
		{
			free (local_env[i]);
			local_env[i] = ft_strdup(var);
			return (local_env);
		}
		i++;
	}
	return (local_env);
}

static char	**update_env(char **local_env, char *var)
{
	int		i;
	int		local_env_size;
	char	**new_env;

	if (var_update(local_env, var) != NULL)
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
	new_env[i++] = ft_strdup(var);
	new_env[i] = NULL;
	free_env(local_env);
	return (new_env);
}

void ft_export(char **argv, char **local_env)
{
	char	*arg;
	char	*equal;
	int		i;
	int		j;

	j = 0;
	if (argv[1] == NULL)
	{
		while (local_env[j])
			printf("declare -x %s\n", local_env[j++]);
		return;
	}
	if (has_options(argv))
		return;
	i = 1;
	while (argv[i] != NULL)
	{
		arg = argv[i];
		equal = ft_strchr(arg, '=');
		if (equal)
			local_env = update_env(local_env, argv[i]);
		i++;
	}
}
