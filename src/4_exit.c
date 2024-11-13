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

static int	valid_code(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "922337203685477580", 18) == 0
		&& arg[18] && arg[18] > '7' && arg[18] <= '9')
		return (0);
	i = 0;
	if (ft_isdigit(arg[i]) || arg[i] == '+' || arg[i] == '-')
		i++;
	else
		return (0);
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	calculate_exit_code(int code)
{
	if (code >= 0)
		return (code % 256);
	else
		return (256 + (code % 256));
}

static int	exit_error(char *arg, int error)
{
	if (error == ERR_ARG)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (error == ERR_NUM)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	return (0);
}

void	ft_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	if (*(argv + 1) == NULL)
	{
		free_shell(shell, EXIT_CMD);
		exit (0);
	}
	if (ft_strncmp(*(argv + 1), "--", 2) == 0
		&& (ft_strlen(*(argv + 1)) == ft_strlen("--")))
		return (ft_exit(argv + 1, shell));
	if (!valid_code(*(argv + 1)))
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
	exit_code = ft_atoi(*(argv + 1));
	free_shell(shell, EXIT_CMD);
	printf("exit\n");
	exit(calculate_exit_code(exit_code));
}
