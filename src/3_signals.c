/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:41:36 by luibarbo          #+#    #+#             */
/*   Updated: 2024/12/03 12:33:12 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_ctrlc = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		if (rl_line_buffer[0] == '\0')
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_ctrlc = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(SIGINT);
	}
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
		g_ctrlc = SIGINT;
}
