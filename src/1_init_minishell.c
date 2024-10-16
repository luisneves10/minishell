/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/16 14:21:45 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_input(char *input, char *prompt)
{
	free (input);
	free (prompt);
}

static char	*get_prompt(t_shell *shell)
{
	char	*prompt;
	char	*user;
	char	*pwd;
	int		home_index;
	int		len_home;

	home_index = var_search(shell->env, "HOME");
	if (home_index >= 0)
		len_home = ft_strlen(shell->env[home_index]) - 5;
	user = shell->env[var_search(shell->env, "USER")] + 5;
	pwd = shell->env[var_search(shell->env, "PWD")] + 4;
	prompt = ft_strjoin_free(ft_strdup("\033[1;34m"), user);
	prompt = ft_strjoin_free(prompt, ":\033[0m");
	if (var_search(shell->env, "HOME") >= 0)
	{
		prompt = ft_strjoin_free(prompt, "~");
		prompt = ft_strjoin_free(prompt, pwd + len_home);
	}
	else
		prompt = ft_strjoin_free(prompt, pwd);
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

void	init_minishell(t_shell *shell)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt(shell);
		input = readline(prompt);
		if (!input)
		{
			printf("exit\n");
			free_input(input, prompt);
			free_env(shell->env); //free struct
			break ;
		}
		if (syntax_check(input) == 0)
		{
			if (*input)
			{
				add_history(input);
				run_cmd(parse_cmd(input), shell);
			}
		}
		free_input(input, prompt);
	}
}
