/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:24:22 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/02 11:42:23 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **argv, char **local_env)
{
	int		i;
	char	*equal;
	char	*arg;

	if (argv[1])
	{
		printf("env: No options or arguments are allowed.\n");
		return ;
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
}
