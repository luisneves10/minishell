/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:19:52 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/24 15:51:58 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*add_redir(t_redir *head, int type,
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

int	parse_quotes(char **ptr_str, char *end_str,
		char **start_tok, char **end_tok)
{
	char	*str;
	int		flag;

	str = *ptr_str;
	*start_tok = str;
	str++;
	flag = 0;
	if (**ptr_str == '"')
		flag = 1;
	while (str < end_str && *str != '"' && flag == 1)
		str++;
	while (str < end_str && *str != '\'' && flag == 0)
		str++;
	*end_tok = str++;
	if (*str == '|' || *str == '<' || *str == '>')
		*ptr_str = str;
	else
		while (str < end_str && *str != ' ' &&
			*str != '|' && *str != '<' && *str != '>')
			str++;
	*end_tok = str;
	str++;
	*ptr_str = str;
	return ('a');
}

int	get_token(char **ptr_str, char *end_str, char **start_tok, char **end_tok)
{
	char	*str;
	int		ret;

	ret = 0;
	str = *ptr_str;
	while (str < end_str && *str == ' ')
		str ++;
	if (*str == '"' || *str == '\'')
		return (parse_quotes(ptr_str, end_str, start_tok, end_tok));
	if (start_tok)
		*start_tok = str;
	ret = special_chars(&str);
	if (ret != 'a')
		str ++;
	while (str < end_str && *str != ' ' && *str != '|' && *str != '>'
		&& *str != '<' && ret == 'a')
		str ++;
	if (end_tok)
		*end_tok = str;
	*ptr_str = str;
	return (ret);
}

int	deal_token(t_execcmd *cmd, char **str, char *end, t_token *token)
{
	int	tok_type;
	int	len;

	tok_type = get_token(str, end, &token->start, &token->end);
	if (tok_type == 0)
		return (0);
	if (tok_type != 'a')
		exit(0);
	len = token->end - token->start;
/*
	-> tratamento da string para tirar as aspas e guardar info se e single
	ou double quotes.

	if (*token->start == '\'')
		literal
	else
		handle das expansoes
*/
	return (1);
}
