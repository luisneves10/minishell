/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:28:33 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/28 10:24:35 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_exit_code(int code)
{
	if (code >= 0)
		return (code % 256);
	else
		return (256 + (code % 256));
}

static void	free_and_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	exit_code = ft_atoi(*(argv + 1));
	free_shell(shell, EXIT_CMD);
	ft_putstr_fd("exit\n", 1);
	exit(calculate_exit_code(exit_code));
}

void	ft_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	if (*(argv + 1) == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_shell(shell, EXIT_CMD);
		exit (0);
	}
	if (ft_strncmp(*(argv + 1), "--", 2) == 0
		&& (ft_strlen(*(argv + 1)) == ft_strlen("--")))
		return (ft_exit(argv + 1, shell));
	if (!valid_code(*(argv + 1))
		|| ((*(argv + 1))[0] == '-' && !(*(argv + 1))[1]))
	{
		exit_code = exit_error(*(argv + 1), ERR_NUM);
		free_shell(shell, EXIT_CMD);
		exit(exit_code);
	}
	if (*(argv + 2))
	{
		shell->exit_status = exit_error("", ERR_ARG);
		return ;
	}
	free_and_exit(argv, shell);
}
