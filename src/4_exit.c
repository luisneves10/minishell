/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:28:33 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/30 11:59:40 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(char **argv, t_shell *shell)
{
	free_shell(shell, 1);
	// free_cmd(shell->cmd);
	if (argv[1] == NULL)
		exit (0);
	if (ft_isnumber(argv[1]))
		exit (ft_atoi(argv[1]));
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit (255);
	}
}
