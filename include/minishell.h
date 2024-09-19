/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:17:38 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/19 11:56:01 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
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

typedef struct	cmd {
	int	type;
} t_cmd;

typedef struct	execcmd
{
	int	type;
	char	*argv[20];
	char	*end_argv[20];
}	t_execcmd;

typedef struct	redircmd {
	int	type;
	t_cmd *cmd;
	char	*file;
	char	*end_file;
	int	mode;
	int	fd;
} t_redircmd;

typedef struct	pipecmd {
	int	type;
	struct	cmd *left;
	struct	cmd *right;
} t_pipecmd;

typedef struct	listcmd {
	int	type;
	struct	cmd *left;
	struct	cmd *right;
}	t_listcmd;

typedef struct	backcmd {
	int	type;
	struct	cmd *cmd;
}	t_backcmd;




void	init_minishell(void);
void	signals();
void	print_user_and_cwd(void);

void	parsecmd(char *str);
int	gettoken(char **ptr_str, char *end_str, char **start_token, char **end_token);
int	special_chars(char *str);
void	nulterminate(t_cmd *cmd);
int	find_char(char **ptr_str, char *end_str, char *set);
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*redircmd(t_cmd	*next_cmd, char *file, char *end_file, int mode, int fd);

#endif
