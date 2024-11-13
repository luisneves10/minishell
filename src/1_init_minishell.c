/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/13 11:34:57 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, int i)
{
	free (shell->prompt);
	free (shell->input);
	g_ctrlc = 0;
	if (i)
	{
		free_env(shell->env);
		if (i == EXIT_EOF)
			printf("exit\n");
		else if (i == EXIT_CMD)
		{
			if (shell->head)
				free_cmd(shell->head);
			if (shell->fds)
			{
				close_fds(shell->fds);
				free (shell->fds);
			}
		}
		free (shell);
		return ;
	}
	shell->prompt = NULL;
	shell->input = NULL;
}

static char	*get_prompt(void)
{
	char	path[4096];
	char	*prompt;
	char	*user;

	prompt = ft_strjoin_free(ft_strdup("\033[1;34m"), "");
	user = getenv("USER");
	if (user)
		prompt = ft_strjoin_free(prompt, user);
	else
		prompt = ft_strjoin_free(prompt, "minishell");
	prompt = ft_strjoin_free(prompt, ":\033[0m");
	prompt = ft_strjoin_free(prompt, getcwd(path, sizeof(path)));
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

void	init_minishell(t_shell *shell)
{
	t_cmd	*cmd;

	while (1)
	{
		shell->prompt = get_prompt();
		shell->input = readline(shell->prompt);
		if (!shell->input)
		{
			free_shell(shell, EXIT_EOF);
			break ;
		}
		add_history(shell->input);
		if (syntax_check(shell) == 0)
		{
			cmd = parse_cmd(shell->input, shell);
			shell->head = cmd;
			if (handle_heredoc(shell) == 0)
				run_cmd(cmd, shell);
			free_cmd(shell->head);
		}
		delete_heredocs(shell, 1);
		free_shell(shell, 0);
	}
	rl_clear_history();
	exit (0);
}
