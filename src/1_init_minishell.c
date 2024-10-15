/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/04 15:07:55 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_input(char *input, char *prompt)
{
	free (input);
	free (prompt);
}

static char	*get_prompt(char **local_env)
{
	char	*prompt;
	char	*user;
	char	*pwd;

	user = local_env[var_search(local_env, "USER")] + 5;
	pwd = local_env[var_search(local_env, "PWD")] + 4;
	prompt = ft_strjoin_free(ft_strdup("\033[1;34m"), user);
	prompt = ft_strjoin_free(prompt, ":\033[0m");
	prompt = ft_strjoin_free(prompt, pwd);
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

void	init_minishell(char *envp[])
{
	char	*input;
	char	*prompt;
	char	**local_env;

	local_env = copy_env(envp);
	while (1)
	{
		prompt = get_prompt(local_env);
		input = readline(prompt);
		if (!input)
		{
			printf("exit\n");
			free_input(input, prompt);
			free_env(local_env);
			break ;
		}
		// syntax_check(input);
		if (*input)
		{
			add_history(input);
			runcmd(parsecmd(input), &local_env);
		}
		free_input(input, prompt);
	}
}
