/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_export3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:32:19 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/15 15:05:30 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_var(t_shell *shell, char *var)
{
	char	*new_var;
	int		i;
	int		j;
	int		flag;

	new_var = malloc(sizeof(char) * ft_strlen(var));
	if (!new_var)
		return ;
	flag = 1;
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '+' && flag)
		{
			flag = 0;
			i++;
		}
		new_var[j++] = var[i++];
	}
	new_var[j] = '\0';
	shell->env = update_env(shell->env, new_var);
	free (new_var);
}

void	append_var(t_shell *shell, char *var)
{
	int		name_len;
	int		i;
	int		flag;
	char	*cpy;

	cpy = var;
	name_len = 0;
	while (var[name_len] && var[name_len] != '+')
		name_len++;
	while (*cpy && *cpy != '=')
		cpy++;
	flag = 1;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, name_len) == 0)
		{
			flag = 0;
			if (ft_strchr(shell->env[i], '='))
				shell->env[i] = ft_strjoin_free(shell->env[i], cpy + 1);
			else
			{
				shell->env[i] = ft_strjoin_free(shell->env[i], "=");
				shell->env[i] = ft_strjoin_free(shell->env[i], cpy + 1);
			}
			return ;
		}
		i++;
	}
	if (flag)
		create_var(shell, var);
}
