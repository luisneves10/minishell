/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/23 15:20:29 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_exec(char **ptr_str, char *end_str, t_shell *shell);

static t_redir	*add_redir(t_redir *head, int type,
					char *start_file, char *end_file)
{
	t_redir	*tmp;
	t_redir	*new_redir;
	int		file_length;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		exit(1);
	memset(new_redir, 0, sizeof(t_redir));
	new_redir->type = type;
	file_length = end_file - start_file;
	new_redir->file = malloc(file_length + 1); // +1 for the null terminator
	if (!new_redir->file)
		exit(1);
	strncpy(new_redir->file, start_file, end_file - start_file);//MUDAR STRNCPY
	new_redir->file[file_length] = '\0';
	new_redir->next = NULL;
	if (!head)
		return (new_redir);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	return (head);
}

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

static int	deal_token(t_execcmd *cmd, char **str, char *end, t_token *token)
{
	int	tok_type;
	int	len;

	tok_type = get_token(str, end, &token->start, &token->end);
	if (tok_type == 0)
		return (0);
	if (tok_type != 'a')
		exit(0);
	len = token->end - token->start;
	cmd->argv[token->argc] = malloc(sizeof(char) * (len + 1));
	if (!cmd->argv[token->argc])
		return (0);
	cmd->argv[token->argc] = ft_strndup(str, len);
	// cmd->end_argv[token->argc] = token->end;
	return (1);
}

static t_cmd	*parse_exec(char **ptr_str, char *end_str, t_shell *shell)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	t_token		*token;

	ret = exec_cmd();
	cmd = (t_execcmd *)ret;
	cmd->argv = malloc(sizeof(char *) * shell->argc + 1);
	if (!cmd->argv)
		return (NULL);
	token = create_token();
	ret = parse_redirs(ret, ptr_str, end_str, shell);
	while (!find_char(ptr_str, end_str, "|"))
	{
		if (!deal_token(cmd, ptr_str, end_str, token))
			break ;
		token->argc++;
		ret = parse_redirs(ret, ptr_str, end_str, shell);
	}
	cmd->argv[shell->argc] = NULL;
	cmd->end_argv[token->argc] = NULL;
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
	null_terminate(cmd);
	return (cmd);
}
