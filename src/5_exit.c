/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:28:33 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/01 11:02:29 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * subject does not require additional arguments in exit
 */

int	ft_exit(void)
{
	printf("exit\n");
	// clear desta merda toda
	exit (0);
}
