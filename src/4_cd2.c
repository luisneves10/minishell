/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:39:37 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/18 17:53:57 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(t_shell *shell)
{
	int		index;
	char	**env;

	env = shell->env;
	index = var_search(env, "PWD");
	if (index >= 0)
		return (shell->env[index] + 4);
	return (NULL);
}

int	var_is_set(char **local_env, char *var)
{
	int	index;

	index = var_search(local_env, var);
	if (index >= 0)
		if (ft_strchr(local_env[index], '='))
			return (1);
	printf("minishell: cd: %s not set\n", var);
	return (0);
}

static void	create_new_var(t_shell *shell, char *var_name, char *var_value)
{
	char	*new_var;

	new_var = ft_strdup(var_name);
	new_var = ft_strjoin_free(new_var, "=");
	new_var = ft_strjoin_free(new_var, var_value);
	shell->env = update_env(shell->env, new_var);
	free (new_var);
}

int	update_var(t_shell *shell, char *var_name, char *var_value)
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
		if (var_value[0])
		{
			new_var = ft_strjoin_free(new_var, "=");
		}
		new_var = ft_strjoin_free(new_var, var_value);
		tmp = shell->env[index];
		shell->env[index] = new_var;
		free (tmp);
	}
	else
		create_new_var(shell, var_name, var_value);
	return (0);
}
