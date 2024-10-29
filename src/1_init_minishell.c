/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/29 11:44:33 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	delete_heredocs(t_shell *shell)
{
	t_heredoc	*current;
	t_heredoc	*temp;

	current = shell->heredoc_head;
	while (current != NULL)
	{
		if (current->fd >= 0)
			close (current->fd);
		if (current->filepath)
		{
			if (unlink(current->filepath) < 0)
				perror("Error deleting heredoc file");
			free(current->filepath);
			current->filepath = NULL;
		}
		if (current->delimiter)
		{
			free(current->delimiter);
			current->delimiter = NULL;
		}
		temp = current;
		current = current->next;
		free(temp);
	}
	shell->heredoc = NULL;
	shell->heredoc_head = NULL;
}

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
		shell->heredoc_flag = 0;
		shell->heredoc = NULL;
		shell->heredoc_head = NULL;
		shell->prompt = get_prompt();
		shell->input = readline(shell->prompt);
		if (!shell->input)
		{
			free_shell(shell, 1);
			printf("exit\n");
			break ;
		}
		add_history(shell->input);
		if (syntax_check(shell) == 0)
		{
			cmd = parse_cmd(shell->input, shell);
			run_cmd(cmd, shell);
			delete_heredocs(shell);
			free_cmd(cmd);
		}
		free_shell(shell, 0);
	}
	rl_clear_history();
	exit (0);
}
