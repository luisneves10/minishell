/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:53:26 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/16 09:46:04 by daduarte         ###   ########.fr       */
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
	int		home_index;
	int		len_home;

	home_index = var_search(local_env, "HOME");
	if (home_index >= 0)
		len_home = ft_strlen(local_env[home_index]) - 5;
	user = local_env[var_search(local_env, "USER")] + 5;
	pwd = local_env[var_search(local_env, "PWD")] + 4;
	prompt = ft_strjoin_free(ft_strdup("\033[1;34m"), user);
	prompt = ft_strjoin_free(prompt, ":\033[0m");
	if (var_search(local_env, "HOME") >= 0)
	{
		prompt = ft_strjoin_free(prompt, "~");
		prompt = ft_strjoin_free(prompt, pwd + len_home);
	}
	else
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
		if (syntax_check(input) == 0)
		{
			if (*input)
			{
				add_history(input);
				run_cmd(parse_cmd(input), &local_env);
			}
		}
		free_input(input, prompt);
	}
}
