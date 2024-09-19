/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/19 11:42:01 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * pwd works even with additional arguments in front
 * it does not work if you attempt to use any flag but -LP
 * For example, if you write "pwd -a", it prints:
 * "bash: pwd: (flag): invalid option"
 * Subject says to build pwd with no options, but how should we handle the
 * additional arguments?
 * */

int	ft_pwd(void)
{
	char	path[1024];

	getcwd(path, sizeof(path));
	printf("%s", path);
	return (0);
}
