/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/16 16:19:17 by daduarte         ###   ########.fr       */
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

	tok = create_token();
	while (find_char(ptr_str, end_str, "<>"))
	{
		printf("str: %s\n", *ptr_str);
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
	return (cmd);
}

static int	deal_token(t_execcmd *cmd, char **str, char *end, t_token *token)
{
	int	tok_type;

	tok_type = get_token(str, end, &token->start, &token->end);
	if (tok_type == 0)
		return (0);
	if (tok_type != 'a')
		exit(0);
	cmd->argv[token->argc] = token->start;
	cmd->end_argv[token->argc] = token->end;
	return (1);
}

static t_cmd	*parse_exec(char **ptr_str, char *end_str)
{
	int			tok;
	t_cmd		*ret;
	t_execcmd	*cmd;
	t_token		*token;

	tok = 0;
	ret = exec_cmd();
	cmd = (t_execcmd *)ret;
	token = create_token();
	ret = parse_redirs(ret, ptr_str, end_str);
	while (!find_char(ptr_str, end_str, "|"))
	{
		if (!deal_token(cmd, ptr_str, end_str, token))
			break ;
		token->argc++;
		ret = parse_redirs(ret, ptr_str, end_str);
	}
	cmd->argv[token->argc] = NULL;
	cmd->end_argv[token->argc] = NULL;
	free(token);
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
	// < test2 wc > test3
	printf("type: %d\n", ((t_redircmd *)cmd)->cmd->type);
	printf("type2: %d\n", ((t_redircmd *)cmd)->type);
	return (cmd);
}
