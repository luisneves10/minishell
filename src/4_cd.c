/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/18 17:54:19 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	cd_home_path(char **argv, t_shell *shell)
{
	char	**env;
	char	*path;
	int		home_index;

	env = shell->env;
	home_index = var_search(shell->env, "HOME");
	if (home_index >= 0)
		path = ft_strjoin(env[home_index] + 5, argv[1] + 1);
	else
	{
		if (shell->home_index != -1)
			path = ft_strjoin(getenv("HOME"), argv[1] + 1);
	}
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (free (path), 1);
	}
	free (path);
	return (0);
}

static	int	cd_minus(t_shell *shell)
{
	char	**env;
	char	path[4096];

	env = shell->env;
	if (var_is_set(shell->env, "OLDPWD"))
	{
		if (chdir(env[var_search(shell->env, "OLDPWD")] + 7) == -1)
		{
			perror("minishell: cd");
			return (1);
		}
		getcwd(path, sizeof(path));
		printf("%s\n", path);
	}
	else
		return (1);
	return (0);
}

static int	change_dir(char **argv, t_shell *shell)
{
	if (argv[1][0] == '~')
		return (cd_home_path(argv, shell));
	else if (ft_strncmp(argv[1], "-", 1) == 0 && ft_strlen(argv[1]) == 1)
		return (cd_minus(shell));
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
	if (!argv[1] || (ft_strncmp(argv[1], "--", 2) == 0
			&& ft_strlen(argv[1]) == 2))
	{
		if (var_is_set(shell->env, "HOME"))
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
