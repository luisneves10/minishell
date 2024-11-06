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
		printf("minishell: %s", str);
		return (-1);
	}
	printf("minishell: syntax error %s\n", str);
	if (error == INV_CHAR)
		return (INV_CHAR);
	else if (error == S_Q)
		return (S_Q);
	else if (error == D_Q)
		return (D_Q);
	else if (error == ERROR_P)
		return (ERROR_P);
	else if (error == ER_TOK)
		return (ER_TOK);
	else if (error == E_NWL)
		return (E_NWL);
	return (1);
}

void	on_off_flag(int *flag)
{
	if (*flag == 1)
		*flag = 0;
	else if (*flag == 0)
		*flag = 1;
}
