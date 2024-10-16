/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:24:22 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/08 15:55:58 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv, char **local_env)
{
	int		i;
	char	*equal;
	char	*arg;

	if (argv[1])
	{
		printf("minishell: env: No options or arguments are allowed\n");
		return (1);
	}
	i = 0;
	while (local_env[i])
	{
		arg = local_env[i];
		equal = ft_strchr(arg, '=');
		if (equal)
			printf("%s\n", local_env[i]);
		i++;
	}
	return (0);
}
