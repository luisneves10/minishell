/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:51:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/15 15:30:16 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
		free (env[i++]);
	free (env);
}

char	**copy_env(char **env)
{
	int		i;
	int		size;
	char	**new_env;

	size = env_size(env);
	new_env = malloc((size + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			perror("ft_strdup");
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	var_name_len(char *var)
{
	int	i;

	if (!var || !var[0])
		return (0);
	i = 0;
	if (ft_strchr(var, '='))
		while (var[i] != '=')
			i++;
	else
		while (var[i])
			i++;
	return (i);
}

int	var_search(char **env, char *var)
{
	int	i;
	int	size;

	i = 0;
	if (!env || !var)
		return (-1);
	while (env[i])
	{
		size = var_name_len(env[i]);
		if (ft_strncmp(env[i], var, size) == 0 && ft_strlen(var) == size)
			return (i);
		i++;
	}
	return (-1);
}
