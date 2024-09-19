/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/19 15:54:37 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parseredirs(t_cmd *cmd, char **ptr_str, char *end_str)
{
	int	token;
	char	*start_tok;
	char	*end_tok;

	while (find_char(ptr_str, end_str, "<>"))
	{
		token = gettoken(ptr_str, end_str, 0, 0);
		if (gettoken(ptr_str, end_str, &start_tok, &end_tok) != 'a')
		{
			printf("missing file for redirection\n");
			break ;
		}
		if (token == '<')
			cmd = redircmd(cmd, start_tok, end_tok, O_RDONLY, 0);
		else if (token == '>')
			cmd = redircmd(cmd, start_tok, end_tok, O_WRONLY|O_CREAT, 1);
		else if (token == '+')
			cmd = redircmd(cmd, start_tok, end_tok, O_WRONLY|O_CREAT, 1);
	}
	return (cmd);
}

static t_cmd	*parseexec(char **ptr_str, char *end_str)
{
	char	*start_token = NULL;
	char	*end_token = NULL;
	t_execcmd	*cmd;
	t_cmd	*ret;
	int	argc = 0;
	int	tok = 0;

	ret = execcmd();
	cmd = (t_execcmd *)ret;
	ret = parseredirs(ret, ptr_str, end_str);
	while (!find_char(ptr_str, end_str, "|"))
	{
		if ((tok = gettoken(ptr_str, end_str, &start_token, &end_token)) == 0)
			break;
		if (tok != 'a')
			exit(0);
		cmd->argv[argc] = start_token;
		cmd->end_argv[argc] = end_token;
		argc ++;
		ret = parseredirs(ret, ptr_str, end_str);
	}
	cmd->argv[argc] = NULL;
	cmd->end_argv[argc] = NULL;
	return (ret);
}

static t_cmd	*parsepipe(char **ptr_str, char *end_str)
{
	t_cmd	*cmd;
	char	*s = NULL, *es = NULL;

	cmd = parseexec(ptr_str, end_str);
	if (find_char(ptr_str, end_str, "|"))
	{
		gettoken(ptr_str, end_str, &s, &es);
		cmd = pipecmd(cmd, parsepipe(ptr_str, end_str));
	}
	return (cmd);
}

void	parsecmd(char *str)
{
	char	*end_str;
	t_cmd	*cmd;

	end_str = str + strlen(str);
	cmd = parsepipe(&str, end_str);
	printf("cmd type: %d\n", cmd->type);
	nulterminate(cmd);
}
