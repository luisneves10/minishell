/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:24:22 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/16 12:23:13 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv, t_shell *shell)
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
	while (shell->env[i])
	{
		arg = shell->env[i];
		equal = ft_strchr(arg, '=');
		if (equal)
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
