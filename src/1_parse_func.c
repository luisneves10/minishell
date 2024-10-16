/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/16 10:01:57 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_exec(char **ptr_str, char *end_str);

static	t_cmd	*handle_redirection(t_cmd *cmd, t_token *tok, int token)
{
	if (token == '<')
		cmd = redir_cmd(cmd, tok, O_RDONLY, 0);
	else if (token == '>')
		cmd = redir_cmd(cmd, tok, O_WRONLY | O_CREAT, 1);
	else if (token == '+')
		cmd = redir_cmd(cmd, tok, O_WRONLY | O_APPEND, 1);
	return (cmd);
}

static t_cmd	*parse_redirs(t_cmd *cmd, char **ptr_str, char *end_str)
{
	t_token	*tok;
	int		token;
	char	*end_tok;
	char	*start_tok;
	//t_execcmd *execcmd;

	tok = create_token();
	while (find_char(ptr_str, end_str, "<>"))
	{
		token = get_token(ptr_str, end_str, 0, 0);
		if (get_token(ptr_str, end_str, &start_tok, &end_tok) != 'a')
		{
			printf("missing file for redirection\n");
			break ;
		}
		tok->start = start_tok;
		tok->end = end_tok;
		cmd = handle_redirection(cmd, tok, token);
	}
	//if (cmd && cmd->type == REDIR && ((t_redircmd *)cmd)->cmd == NULL)
		//((t_redircmd *)cmd)->cmd = parse_exec(ptr_str, end_str);
	//execcmd = (t_execcmd *)((t_redircmd *)cmd)->cmd;
	//printf("command: %s\n", execcmd->argv[0]);
	return (cmd);
}

static t_cmd	*parse_exec(char **ptr_str, char *end_str)
{
	int			tok;
	int			argc;
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*end_token;
	char		*start_token;

	tok = 0;
	argc = 0;
	ret = exec_cmd();
	cmd = (t_execcmd *)ret;
	ret = parse_redirs(ret, ptr_str, end_str);
	while (!find_char(ptr_str, end_str, "|"))
	{
		tok = get_token(ptr_str, end_str, &start_token, &end_token);
		if (tok == 0)
			break ;
		if (tok != 'a')
			exit(0);
		cmd->argv[argc] = start_token;
		cmd->end_argv[argc] = end_token;
		argc ++;
		ret = parse_redirs(ret, ptr_str, end_str);
	}
	cmd->argv[argc] = NULL;
	cmd->end_argv[argc] = NULL;
	return (ret);
}

static t_cmd	*parse_pipe(char **ptr_str, char *end_str)
{
	t_cmd		*cmd;
	char		*s;
	char		*es;

	s = NULL;
	es = NULL;
	cmd = parse_exec(ptr_str, end_str);
	while (find_char(ptr_str, end_str, "|"))
	{
		get_token(ptr_str, end_str, &s, &es);
		cmd = pipe_cmd(cmd, parse_pipe(ptr_str, end_str));
	}
	return (cmd);
}

t_cmd	*parse_cmd(char *str)
{
	char	*end_str;
	t_cmd	*cmd;

	end_str = str + ft_strlen(str);
	cmd = parse_pipe(&str, end_str);
	null_terminate(cmd);
	return (cmd);
}
