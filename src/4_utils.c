/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:46:33 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/18 16:59:19 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_options(char **argv, char *command)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if ((ft_strncmp(argv[i], "-", 1) == 0 && ft_strlen(argv[i]) == 1)
			|| (ft_strncmp(argv[i], "--", 2) == 0 && ft_strlen(argv[i]) == 2))
			return (0);
		if (argv[i][0] == '-')
		{
			printf("minishell: %s: %s: Invalid option\n", command, argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
