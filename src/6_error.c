/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:14:57 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/06 16:15:43 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_error(char *str, int error, t_shell *shell)
{
	shell->exit_status = error;
	if (error == -1)
	{
		shell->exit_status = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	ft_putstr_fd("minishell: syntax error ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	on_off_flag(int *flag)
{
	if (*flag == 1)
		*flag = 0;
	else if (*flag == 0)
		*flag = 1;
}
