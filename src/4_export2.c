/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:06:17 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/02 15:39:14 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	sort_env(char **env)
{
} */

void	ft_export_no_args(char **local_env)
{
	char	**env_copy;
	int		i;
	int		j;

	env_copy = copy_env(local_env);
	// sort_env(env_copy);
	i = 0;
	while (env_copy[i])
	{
		j = 0;
		printf("declare -x ");
		while (env_copy[i][j] && env_copy[i][j] != '=')
			printf("%c", env_copy[i][j++]);
		printf("%c", env_copy[i][j++]);
		printf("\"%s\"\n", env_copy[i]);
		i++;
	}
	free_env(env_copy);
}
