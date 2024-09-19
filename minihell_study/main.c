
#include "minishell.h"

int	getcmd(char **buf, int nbuf)
{
	char	path[1024];

	getcwd(path, sizeof(path));
	printf("~%s", path);
	*buf = readline("$ ");
	if (buf[0] == NULL)
		return (-1);
	if (**buf)
		add_history(*buf);
	buf[strlen(*buf) - 1] = 0;
	return (0);
}

/* void	parsecmd(char *str)
{
	char	*end_str;
	char	*start_token = NULL, *end_token = NULL;
	t_execcmd	*cmd;
	int	argc = 0;

	cmd = execcmd();
	end_str = str + strlen(str);
	while (str < end_str)
	{
		printf("token: %c\n", gettoken(&str, end_str, &start_token, &end_token));
		cmd->argv[argc] = start_token;
		cmd->end_argv[argc] = end_token;
		argc ++;
		printf("args: %d\n", argc);
	}
	cmd->argv[argc] = NULL;
	cmd->end_argv[argc] = NULL;
	nulterminate(cmd);
} */

int	main(void)
{
	char	*buf;
	char	*str;

	while (getcmd(&buf, sizeof(buf)) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			char *path = buf + 3;
			if (chdir(path) < 0)
				fprintf(stderr, "you dont have any directory called that you fukker %s\n", str+3);
			continue;
		}
		else
		{
			parsecmd(buf);
			//printf("You entered: %s\n", buf);
		}
	}
	return (0);
}
