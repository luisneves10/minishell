/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/15 22:37:22 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parseexec(char **ptr_str, char *end_str);

static t_cmd	*parseredirs(t_cmd *cmd, char **ptr_str, char *end_str)
{
	t_token	*tok;
	int		token;
	char	*end_tok;
	char	*start_tok;

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
			cmd = redircmd(cmd, tok, O_WRONLY | O_CREAT, 1);
		else if (token == '+')
			cmd = redircmd(cmd, tok, O_WRONLY | O_APPEND, 1);
	}
	if (cmd && cmd->type == REDIR && ((t_redircmd *)cmd)->cmd == NULL)
    {
        ((t_redircmd *)cmd)->cmd = parseexec(ptr_str, end_str);
    }
	return (cmd);
}

static t_cmd	*parseexec(char **ptr_str, char *end_str)
{
	int			tok;
	int			argc;
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*end_token;
	char		*start_token;

	tok = 0;
	argc = 0;
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	ret = parseredirs(ret, ptr_str, end_str);
	while (!find_char(ptr_str, end_str, "|"))
	{
		tok = gettoken(ptr_str, end_str, &start_token, &end_token);
		if (tok == 0)
			break ;
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
	t_cmd		*cmd;
	char		*s;
	char		*es;

	s = NULL;
	es = NULL;
	cmd = parseexec(ptr_str, end_str);
	while (find_char(ptr_str, end_str, "|"))
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
	return (cmd);
}
