/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/15 14:55:47 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	// if (!var_value)
	// 	return (1);
	index = var_search(shell->env, var_name);
	if (index >= 0)
	{
		new_var = ft_strjoin_free(ft_strdup(""), var_name);
		if (var_value[0])
		{
			new_var = ft_strjoin_free(new_var, "=");
		}
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
	if (argv[1][0] == '~')
	{
		if (home_index >= 0)
			path = ft_strjoin(env[home_index] + 5, argv[1] + 1);
		else
			path = ft_strjoin(getenv("HOME"), argv[1] + 1);
		if (chdir(path) == -1)
		{
			perror("minishell: cd");
			return (free (path), 1);
		}
		free (path);
	}
	else if (argv[1][0] && chdir(argv[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	ft_cd(char **argv, t_shell *shell)
{
	char	**env;
	char	path[4096];
	char	*tmp;

	env = shell->env;
	if (has_options(argv, "cd"))
		return (1);
	if (shell->argc > 1 && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	tmp = getcwd(path, sizeof(path));
	if (!argv[1])
	{
		if (home_is_set(shell->env))
			chdir(env[var_search(shell->env, "HOME")] + 5);
		else
			return (1);
	}
	else
		if (change_dir(argv, shell) == 1)
			return (1);
	update_var(shell, "OLDPWD", tmp);
	update_var(shell, "PWD", getcwd(path, sizeof(path)));
	return (0);
}
