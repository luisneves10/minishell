/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:06:17 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/10 12:18:37 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var_value(char **env_copy, int i, int j)
{
	if (env_copy[i][j] != '\0')
	{
		printf("%c", env_copy[i][j++]);
		printf("\"");
		while (env_copy[i][j])
		{
			if (env_copy[i][j] == '$')
				printf("\\");
			printf("%c", env_copy[i][j++]);
		}
		printf("\"");
	}
}

static int	smaller_var(int size1, int size2)
{
	if (size1 < size2)
		return (size1);
	return (size2);
}

static void	sort_env(char **env)
{
	int		i;
	int		j;
	int		size1;
	int		size2;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j + 1])
		{
			size1 = var_name_len(env[j]);
			size2 = var_name_len(env[j + 1]);
			if (ft_strncmp(env[j], env[j + 1], smaller_var(size1, size2)) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export_no_args(char **local_env)
{
	char	**env_copy;
	int		i;
	int		j;

	env_copy = copy_env(local_env);
	sort_env(env_copy);
	i = -1;
	while (env_copy[++i])
	{
		j = 0;
		printf("declare -x ");
		while (env_copy[i][j] && env_copy[i][j] != '=')
			printf("%c", env_copy[i][j++]);
		print_var_value(env_copy, i, j);
		printf("\n");
	}
	free_env(env_copy);
}
