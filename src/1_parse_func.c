/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/24 13:10:32 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_exec(char **ptr_str, char *end_str, t_shell *shell);

static t_cmd	*parse_redirs(t_cmd *cmd, char **ptr_str,
					char *end_str, t_shell *shell)
{
	t_token		*tok;
	int			token;
	char		*end_tok;
	char		*start_tok;
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	tok = create_token();
	while (find_char(ptr_str, end_str, "<>"))
	{
		token = get_token(ptr_str, end_str, 0, 0);
		if (get_token(ptr_str, end_str, &start_tok, &end_tok) != 'a')
		{
			printf("missing file for redirection\n");
			break ;
		}
		if (token == '-')
			shell->delimiter = get_delimiter(start_tok, end_tok);
		else
			ecmd->redir = add_redir(ecmd->redir, token, start_tok, end_tok);
	}
	free(tok);
	return (cmd);
}

static t_cmd	*parse_exec(char **ptr_str, char *end_str, t_shell *shell)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	t_token		*token;

	shell->argc = 0;
	token_count(*ptr_str, shell);
	ret = exec_cmd(shell);
	cmd = (t_execcmd *)ret;
	token = create_token();
	ret = parse_redirs(ret, ptr_str, end_str, shell);
	while (!find_char(ptr_str, end_str, "|"))
	{
		if (!deal_token(cmd, ptr_str, end_str, token))
			break ;
		token->argc++;
		ret = parse_redirs(ret, ptr_str, end_str, shell);
	}
	free(token);
	return (ret);
}

static t_cmd	*parse_pipe(char **ptr_str, char *end_str, t_shell *shell)
{
	t_cmd	*cmd;
	char	*s;
	char	*es;

	s = NULL;
	es = NULL;
	cmd = parse_exec(ptr_str, end_str, shell);
	while (find_char(ptr_str, end_str, "|"))
	{
		get_token(ptr_str, end_str, &s, &es);
		cmd = pipe_cmd(cmd, parse_pipe(ptr_str, end_str, shell));
	}
	return (cmd);
}

t_cmd	*parse_cmd(char *str, t_shell *shell)
{
	char	*end_str;
	t_cmd	*cmd;

	end_str = str + ft_strlen(str);
	cmd = parse_pipe(&str, end_str, shell);
	return (cmd);
}
