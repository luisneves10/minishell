/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:17:38 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/13 14:18:15 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <signal.h>
#include "../libft/include/libft.h"
#include "../libft/include/ft_printf.h"
#include "../libft/include/get_next_line.h"

void	init_minishell(void);
void	signals();
void	print_user_and_cwd(void);

#endif
