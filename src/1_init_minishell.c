/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/23 12:11:04 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, int i)
{
	free (shell->prompt);
	free (shell->input);
	if (i)
	{
		free_env(shell->env);
		free (shell);
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
			printf("exit\n");
			break ;
		}
		if (syntax_check(shell->input) == 0)
		{
			if (*shell->input)
			{
				add_history(shell->input);
				cmd = parse_cmd(shell->input);
				run_cmd(cmd, shell);
				free_cmd(cmd);
			}
		}
		/* printf("####################\n");
		printf("# Exit Status: %3d #\n", shell->exit_status);
		printf("####################\n"); */
		free_shell(shell, 0);
	}
}
