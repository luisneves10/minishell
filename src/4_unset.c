/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:42:31 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/16 12:22:50 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var(char **local_env, char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		i++;
	}
	i = 0;
	while (local_env[i])
	{
		if (ft_strncmp(local_env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	**remove_var(char **local_env, char *var)
{
	int		i;
	int		j;
	int		size;
	char	**new_env;

	size = env_size(local_env);
	new_env = malloc(size * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (local_env[i])
	{
		if (ft_strncmp(local_env[i], var, ft_strlen(var)) == 0)
			i++;
		else
			new_env[j++] = ft_strdup(local_env[i++]);
	}
	new_env[j] = NULL;
	free_env(local_env);
	return (new_env);
}

int	ft_unset(char **argv, t_shell *shell)
{
	int	i;

	if (!argv[1])
		return (1);
	if (has_options(argv, argv[0]))
		return (2);
	i = 1;
	while (argv[i] != NULL)
	{
		if (is_var(shell->env, argv[i]))
			shell->env = remove_var(shell->env, argv[i]);
		i++;
	}
	return (0);
}
