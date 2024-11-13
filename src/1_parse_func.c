/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/13 15:37:22 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_redirs(t_cmd *cmd, char **ptr_str, t_shell *shell)
{
	t_token		*tok;
	int			token;
	char		*end_tok;
	char		*start_tok;

	tok = create_token();
	while (find_char(ptr_str, "<>"))
	{
		token = get_token(ptr_str, 0, 0);
		if (get_token(ptr_str, &start_tok, &end_tok) != 'a')
		{
			printf("missing file for redirection\n");
			break ;
		}
		if (token == '-')
		{
			shell->heredoc = get_delimiter(start_tok, end_tok, shell);
			shell->heredoc_flag = 1;
		}
		tok->start = start_tok;
		tok->end = end_tok;
		cmd->redir = add_redir(cmd->redir, token, tok, shell);
	}
	free(tok);
	return (cmd);
}

static t_cmd	*parse_exec(char **ptr_str, t_shell *shell)
{
	t_cmd		*cmd;
	t_cmd		*ret;
	t_token		*token;

	shell->argc = 0;
	token_count(*ptr_str, shell);
	ret = create_cmd(shell, EXEC, NULL, NULL);
	cmd = ret;
	token = create_token();
	ret = parse_redirs(ret, ptr_str, shell);
	while (!find_char(ptr_str, "|"))
	{
		if (!deal_token(cmd, ptr_str, token, shell))
			break ;
		token->argc++;
		ret = parse_redirs(ret, ptr_str, shell);
	}
	free(token);
	return (ret);
}

static t_cmd	*parse_pipe(char **ptr_str, t_shell *shell)
{
	char	*s;
	char	*es;
	t_cmd	*cmd;

	s = NULL;
	es = NULL;
	cmd = parse_exec(ptr_str, shell);
	cmd->argv = clean_argv(cmd);
	while (find_char(ptr_str, "|"))
	{
		get_token(ptr_str, &s, &es);
		cmd = create_cmd(shell, PIPE, cmd, parse_pipe(ptr_str, shell));
	}
	return (cmd);
}

t_cmd	*parse_cmd(char *str, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = parse_pipe(&str, shell);
	return (cmd);
}
