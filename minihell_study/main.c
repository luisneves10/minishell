#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

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

int	special_chars(char *str)
{
	if (*str == '|')
		return ('|');
	else if (*str == '(')
		return ('(');
	else if (*str == ')')
		return (')');
	else if (*str == ';')
		return (';');
	else if (*str == '<')
		return ('<');
	else if (*str == '>')
	{
		str++;
		if (*str == '>')
			return ('+');
	}
	else if (*str == 0)
		return (0);
	return ('a');
}

int	gettoken(char **ptr_str, char *end_str, char **start_token, char **end_token)
{
	char	*str;
	int	ret;

	str = *ptr_str;
	while (str < end_str && *str == ' ')
		str ++;
	if (str)
	{
		*start_token = str;
		ret = special_chars(str);
	}
	while (str < end_str && *str != ' ')
	{
		str ++;
	}
	*end_token = str;
	*ptr_str = str;
	return (ret);
}

t_cmd	*execcmd(void)
{
	struct execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	if (!cmd)
		exit(0);
	memset(cmd, 0, sizeof(t_execcmd));
	cmd->type = EXEC;
	return ((t_cmd*)cmd);
}

void	nulterminate(t_cmd *cmd)
{
	t_execcmd *ecmd;
	int	i;

	i = 0;
	if (cmd == NULL)
		exit(0);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->argv[i])
		{
			*ecmd->end_argv[i] = '\0';
			printf("token %d: %s\n", i, ecmd->argv[i]);
			i ++;
		}
	}
}

int	find_char(char **ptr_str, char *end_str, char *set)
{
	char	*s;

	s = *ptr_str;
	while (s < end_str && strchr(" ", *s))
		s++;
	*ptr_str = s;
	return (*s && strchr(set, *s));
}

t_cmd	*parseexec(char **ptr_str, char *end_str)
{
	char	*start_token = NULL;
	char	*end_token = NULL;
	t_execcmd	*cmd;
	t_cmd	*ret;
	int	argc = 0;
	int	tok = 0;
	int	i = 0;

	ret = execcmd();
	cmd = (t_execcmd *)ret;
	//ret = parseredirs(ret, ptr_str, end_str);
	while (!find_char(ptr_str, end_str, "|"))
	{
		if ((tok = gettoken(ptr_str, end_str, &start_token, &end_token)) == 0)
			break;
		if (tok != 'a')
			exit(0);
		cmd->argv[argc] = start_token;
		cmd->end_argv[argc] = end_token;
		argc ++;
		//ret = parseredirs(ret, ptr_str, end_str);
	}
	cmd->argv[argc] = NULL;
	cmd->end_argv[argc] = NULL;
	while (i < argc)
	{
		//printf("token %d: %s\n", i, cmd->argv[i]);
		i ++;
	}
	return (ret);
}

t_cmd	*parsepipe(char **ptr_str, char *end_str)
{
	t_cmd	*cmd;

	cmd = parseexec(ptr_str, end_str);
	if (find_char(ptr_str, end_str, "|"))
	{
		printf("ERROR HERE\n");
		gettoken(ptr_str, end_str, 0, 0);
		//cmd = pipecmd(cmd, parsepipe(ptr_str, end_str));
	}
	return (cmd);
}

void	parsecmd(char *str)
{
	char	*end_str;
	t_cmd	*cmd;

	end_str = str + strlen(str);
	cmd = parsepipe(&str, end_str);
	nulterminate(cmd);
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
			printf("You entered: %s\n", buf);
		}
	}
	return (0);
}
