/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/01 12:09:51 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parseredirs(t_cmd *cmd, char **ptr_str, char *end_str)
{
	int	token;
	t_token	*tok;
	char	*start_tok;
	char	*end_tok;

	tok = create_token();
	while (find_char(ptr_str, end_str, "<>"))
	{
		token = gettoken(ptr_str, end_str, 0, 0);
		if (gettoken(ptr_str, end_str, &start_tok, &end_tok) != 'a')
		{
			printf("missing file for redirection\n");
			break ;
		}
		tok->start = start_tok;
		tok->end = end_tok;
		if (token == '<')
			cmd = redircmd(cmd, tok, O_RDONLY, 0);
		else if (token == '>')
			cmd = redircmd(cmd, tok, O_WRONLY|O_CREAT, 1);
		else if (token == '+')
			cmd = redircmd(cmd, tok, O_WRONLY|O_CREAT, 1);
	}
	return (cmd);
}

static t_cmd	*parseexec(char **ptr_str, char *end_str)
{
	char	*start_token;
	char	*end_token;
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
	char	*s = NULL;
	char	*es = NULL;

	cmd = parseexec(ptr_str, end_str);
	if (find_char(ptr_str, end_str, "|"))
	{
		gettoken(ptr_str, end_str, &s, &es);
		cmd = pipecmd(cmd, parsepipe(ptr_str, end_str));
	}
	return (cmd);
}

t_cmd	*parsecmd(char *str)
{
	char	*end_str;
	t_cmd	*cmd;

	end_str = str + ft_strlen(str);
	cmd = parsepipe(&str, end_str);
	nulterminate(cmd);
	//t_pipecmd *piped = (t_pipecmd *)cmd;
	//t_execcmd *left = (t_execcmd *)piped->left;
	//t_redircmd *right = (t_redircmd *)piped->right;
	//t_execcmd *rightcmd = (t_execcmd *)right;
	//printf("left command: %s\n", left->argv[0]);
	//printf("right command: %s\n", rightcmd->argv[0]);
	return (cmd);
}
