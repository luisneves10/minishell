/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:42 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/10 12:31:23 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv)
{
	char	path[4096];

	if (has_options(argv, argv[0]))
		return (2);
	if (getcwd(path, sizeof(path)))
		ft_putendl_fd(path, 1);
	return (0);
}
