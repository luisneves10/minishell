/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/16 12:21:15 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * $HOME not defined: se executar "cd" --> "bash: cd: HOME not set"
 * $HOME defined : se executar "cd" --> vai para o HOME
 * "cd <arg1> <arg2> <arg3>" --> muda para o caminho definido em <arg1>
 * todos os args a frente do primeiro sao ignorados
 * se o comando for executado com sucesso, $PWD e $OLD_PWD levam update
 */

static int	home_is_set(char **local_env)
{
	int	index;

	index = var_search(local_env, "HOME");
	if (index >= 0)
		if (ft_strchr(local_env[index], '='))
			return (1);
	printf("minishell: cd: HOME not set\n");
	return (0);
}

static int	update_var(t_shell *shell, char *var_name, char *var_value)
{
	int		index;
	char	*new_var;
	char	*tmp;

	if (!var_value)
		return (1);
	index = var_search(shell->env, var_name);
	if (index >= 0)
	{
		new_var = ft_strjoin_free(ft_strdup(""), var_name);
		new_var = ft_strjoin_free(new_var, "=");
		new_var = ft_strjoin_free(new_var, var_value);
		tmp = shell->env[index];
		shell->env[index] = new_var;
		free (tmp);
	}
	return (0);
}

static int	change_dir(char **argv, t_shell *shell)
{
	char	**env;
	char	*path;
	int		home_index;

	env = shell->env;
	home_index = var_search(shell->env, "HOME");
	if (argv[1][0] == '~' && argv[1][1] == '\0')
	{
		argv[1]++;
		path = ft_strjoin(env[home_index] + 5, argv[1]);
		if (chdir(path) == -1)
		{
			perror("minishell: cd");
			free (path);
			return (1);
		}
		free (path);
	}
	else if (chdir(argv[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	ft_cd(char **argv, t_shell *shell)
{
	char	**env;
	char	path[1024];

	env = shell->env;
	if (has_options(argv, "cd"))
		return (1);
	if (!argv[1])
	{
		if (home_is_set(shell->env))
			chdir(env[var_search(shell->env, "HOME")] + 5);
		else
			return (1);
	}
	else
	{
		if (change_dir(argv, shell) == 1)
			return (1);
	}
	update_var(shell, "OLDPWD", env[var_search(shell->env, "PWD")] + 4);
	update_var(shell, "PWD", getcwd(path, sizeof(path)));
	return (0);
}
