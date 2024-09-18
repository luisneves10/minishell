/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:02 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/18 12:15:42 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_user_and_cwd(void)
{
	char	*username;
	char	path[1024];

	username = getenv("LOGNAME");
	getcwd(path, sizeof(path));
	printf("\033[1;34m%s:\033[0;36m~%s", username, path);
}
