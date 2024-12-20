/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:58:25 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/05 16:04:23 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_builtin(t_cmd *execcmd)
{
	if (ft_strncmp(execcmd->argv[0], "echo", 4) == 0
		&& ft_strlen(execcmd->argv[0]) == 4)
		return ("echo");
	else if (ft_strncmp(execcmd->argv[0], "cd", 2) == 0
		&& ft_strlen(execcmd->argv[0]) == 2)
		return ("cd");
	else if (ft_strncmp(execcmd->argv[0], "pwd", 3) == 0
		&& ft_strlen(execcmd->argv[0]) == 3)
		return ("pwd");
	else if (ft_strncmp(execcmd->argv[0], "export", 6) == 0
		&& ft_strlen(execcmd->argv[0]) == 6)
		return ("export");
	else if (ft_strncmp(execcmd->argv[0], "unset", 5) == 0
		&& ft_strlen(execcmd->argv[0]) == 5)
		return ("unset");
	else if (ft_strncmp(execcmd->argv[0], "env", 3) == 0
		&& ft_strlen(execcmd->argv[0]) == 3)
		return ("env");
	else if (ft_strncmp(execcmd->argv[0], "exit", 4) == 0
		&& ft_strlen(execcmd->argv[0]) == 4)
		return ("exit");
	return (NULL);
}

void	exec_builtin(char **argv, char *builtin, t_shell *shell)
{
	if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
		shell->exit_status = ft_echo(argv);
	else if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
		shell->exit_status = ft_cd(argv, shell);
	else if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
		shell->exit_status = ft_pwd(argv);
	else if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
		shell->exit_status = ft_export(argv, shell);
	else if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0)
		shell->exit_status = ft_unset(argv, shell);
	else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
		shell->exit_status = ft_env(argv, shell);
	else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
		ft_exit(argv, shell);
}
