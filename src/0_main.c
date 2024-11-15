/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:58:12 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/15 14:08:09 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ctrlc = 0;

int	main(int argc, char **argv, char *envp[])
{
	t_shell	*shell;

	shell = init_struct(argv, envp);
	if (!shell)
		return (1);
	if (argc != 1 || argv[1])
		return (0);
	signals();
	init_minishell(shell);
	return (0);
}
