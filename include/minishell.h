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
# include <signal.h>
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

# define EXEC  1
# define REDIR 2
# define PIPE  3
# define LIST  4
# define BACK  5

typedef struct	cmd
{
	int	type;
}	t_cmd;

typedef struct	execcmd
{
	int		type;
	char	*argv[20];
	char	*end_argv[20];
}	t_execcmd;

typedef struct	redircmd
{
	int			type;
	struct	cmd *cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}	t_redircmd;

typedef struct	pipecmd
{
	int			type;
	struct	cmd *left;
	struct	cmd *right;
}	t_pipecmd;

typedef struct	listcmd
{
	int			type;
	struct	cmd *left;
	struct	cmd *right;
}	t_listcmd;

typedef struct	backcmd
{
	int			type;
	struct	cmd *cmd;
}	t_backcmd;

/* =========================================================================== */
/*	FUNCTIONS                                                                  */
/* =========================================================================== */

void	init_minishell(void);
void	signals();
void	print_user_and_cwd(void);

t_cmd	*parsecmd(char *str);
int		gettoken(char **ptr_str, char *end_str, char **start_token, char **end_token);
int		special_chars(char *str);
void	nulterminate(t_cmd *cmd);
int		find_char(char **ptr_str, char *end_str, char *set);
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);

void	runcmd(t_cmd *cmd);

int		ft_pwd(char **argv);
int		ft_cd(char **argv);

#endif