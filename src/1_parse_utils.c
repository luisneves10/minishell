/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:19:52 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/23 13:04:30 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*add_redir(t_redir *head, int type, char *start_file, char *end_file)
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

/* int	parse_quotes(char **ptr_str, char **start_tok, char **end_tok)
{
	char	*str;
	int		flag;

	str = *ptr_str;
	*start_tok = str;
	str++;
	flag = 0;
	if (**ptr_str == '"')
		flag = 1;
	while (*str && *str != '"' && flag == 1)
		str++;
	while (*str && *str != '\'' && flag == 0)
		str++;
	*end_tok = str++;
	if (*str == '|' || *str == '<' || *str == '>')
		*ptr_str = str;
	else
		while (*str && *str != ' ' &&
			*str != '|' && *str != '<' && *str != '>')
			str++;
	*end_tok = str;
	str++;
	*ptr_str = str;
	return ('a');
} */

/* int	parse_quotes(char **ptr_str, char *str, char **start_tok, char **end_tok)
{
	char	quote_type;
	int		in_quotes;

	in_quotes = 0;
	*start_tok = str;
	while (*str)
	{
		while (*str && !find_char(&str, " |\"\'"))
			str++;
		if (*str == '"' || *str == '\'')
		{
			quote_type = **ptr_str;
			in_quotes = 1;
			str++;
			while (*str && *str != quote_type)
				str++;
			if (*str == quote_type)
				in_quotes = 0;
			str++;
		}
		if (*str == ' ' || *str == '|')
			break ;
	}
	*end_tok = str++;
	*ptr_str = str;
	return ('a');
}

int	get_token(char **ptr_str, char **start_tok, char **end_tok)
{
	char	*str;
	int		ret;

	ret = 0;
	str = *ptr_str;
	while (*str && *str == ' ')
		str ++;
	if (*str == '"' || *str == '\'')
		return (parse_quotes(ptr_str, str, start_tok, end_tok));
	if (start_tok)
		*start_tok = str;
	ret = special_chars(&str);
	if (ret != 'a')
		str ++;
	while (*str && *str != ' ' && *str != '|' && *str != '>'
		&& *str != '<' && ret == 'a')
		str ++;
	if (end_tok)
		*end_tok = str;
	*ptr_str = str;
	return (ret);
} */

int	token_has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	parse_quotes(char **ptr_str, char *str, char **start_tok, char **end_tok)
{
	char	quote_type;

	*start_tok = str;
	while (*str)
	{
		while (*str && !find_char(&str, " |\"\'"))
			str++;
		if (*str == '"' || *str == '\'')
		{
			quote_type = *str;
			str++;
			while (*str && *str != quote_type)
				str++;
			if (*str && *str == quote_type)
				str++;
		}
		if (*str == ' ' || *str == '|')
			break ;
	}
	*end_tok = str++;
	*ptr_str = str;
	return ('a');
}

int	get_token(char **ptr_str, char **start_tok, char **end_tok)
{
	char	*str;
	int		ret;

	ret = 0;
	str = *ptr_str;

	while (*str && *str == ' ')
		str++;
	if (token_has_quotes(str))
		return (parse_quotes(ptr_str, str, start_tok, end_tok));
	if (start_tok)
		*start_tok = str;
	ret = special_chars(&str);
	if (ret != 'a')
		str ++;
	while (*str && *str != ' ' && *str != '|' && *str != '>'
		&& *str != '<' && ret == 'a')
		str ++;
	if (end_tok)
		*end_tok = str;
	*ptr_str = str;
	return (ret);
}

int	deal_token(t_execcmd *cmd, char **str, t_token *token, t_shell *shell)
{
	int	tok_type;
	int	len;
	t_shell	*sh; // DELETE DELETE DELETE DELETE DELETE DELETE DELETE

	tok_type = get_token(str, &token->start, &token->end);
	if (tok_type == 0)
		return (0);
	if (tok_type != 'a')
		exit(0);
	len = token->end - token->start;
	cmd->argv[token->argc] = ft_strndup(token->start, len);
	printf("TOKEN: %s\n", cmd->argv[token->argc]); // DELETE DELETE DELETE DELETE
	printf("______________________________\n"); // DELETE DELETE DELETE DELETE
	sh = shell; // DELETE DELETE DELETE DELETE DELETE DELETE
	sh = (void *)sh; // DELETE DELETE DELETE DELETE DELETE DELETE
	return (1);
}
