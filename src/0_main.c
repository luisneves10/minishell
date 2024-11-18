/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:58:12 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/18 17:36:01 by daduarte         ###   ########.fr       */
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
	shell->home_index = var_search(envp, "HOME");
	if (argc != 1 || argv[1])
		return (0);
	signals();
	init_minishell(shell);
	return (0);
}
