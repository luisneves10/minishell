/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/30 13:12:30 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	free_shell(t_shell *shell, int i)
{
	free (shell->prompt);
	free (shell->input);
	if (i)
	{
		free_env(shell->env);
		free (shell);
		if (i == 1)
			printf("exit\n");
		return ;
	}
	shell->prompt = NULL;
	shell->input = NULL;
}

static char	*get_prompt(void)
{
	char	path[1024];
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
			free_shell(shell, 1);
			break ;
		}
		add_history(shell->input);
		if (syntax_check(shell) == 0)
		{
			cmd = parse_cmd(shell->input, shell);
			if (shell->heredoc_flag == 1)
				handle_heredoc(shell);
			run_cmd(cmd, shell);
			free_cmd(cmd);
		}
		delete_heredocs(shell, 1);
		free_shell(shell, 0);
	}
	rl_clear_history();
	exit (0);
}
