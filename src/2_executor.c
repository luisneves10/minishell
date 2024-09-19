/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:37:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/19 12:48:54 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	runcmd(t_cmd *cmd)
{
	t_execcmd	*execcmd;

	execcmd = (t_execcmd *)cmd;
	if (ft_strncmp(execcmd->argv[0], "cd", 2) == 0)
		ft_cd(execcmd->argv);
	if (ft_strncmp(execcmd->argv[0], "pwd", 3) == 0)
		ft_pwd(execcmd->argv);
}
