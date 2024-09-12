#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*getcmd(char *buf, int nbuf)
{
	char	*str;
	char	path[1024];

	getcwd(path, sizeof(path));
	printf("~%s", path);
	buf = readline("$ ");
	str = strdup(buf);
	if (buf == NULL)
		return (NULL);
	if (*buf)
		add_history(buf);
	buf[strlen(buf) - 1] = 0;
	return (str);
}

int	main(void)
{
	char	buf[1024];
	char	*str;

	while (1)
	{
		str = getcmd(buf, sizeof(buf));
		if (str)
		{
			//DEAL WITH CD
			if (str[0] == 'c' && str[1] == 'd' && str[2] == ' ')
			{
				char *path = str + 3;
				if (chdir(path) < 0)
					fprintf(stderr, "you dont have any directory called that you fukker %s\n", str+3);
				continue;
			}
			printf("You entered: %s\n", str);
		}
	}
	exit(0);
}
