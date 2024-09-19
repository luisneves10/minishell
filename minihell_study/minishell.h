#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	struct	cmd *cmd;
	char	*file;
	char	*efile;
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

#endif
