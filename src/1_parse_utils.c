/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:19:52 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/15 15:43:04 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_whitespace(str[i]))
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

	if (start_tok)
		*start_tok = str;
	while (*str)
	{
		while (*str && !is_whitespace(*str) && !find_char(&str, "\"\'"))
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
		if (is_whitespace(*str) || *str == '|' || *str == '<' || *str == '>')
			break ;
	}
	if (end_tok)
		*end_tok = str;
	*ptr_str = str;
	return ('a');
}

int	special_chars(char **str)
{
	if (**str == '|')
		return ('|');
	else if (**str == '<' || **str == '>')
		return (special_redirs(str));
	else if (**str == 0)
		return (0);
	return ('a');
}

int	get_token(char **ptr_str, char **start_tok, char **end_tok)
{
	char	*str;
	int		ret;

	if (!ptr_str || !(*ptr_str))
		return (0);
	ret = 0;
	str = *ptr_str;
	while (*str && is_whitespace(*str))
		str++;
	if (token_has_quotes(str) && (*str != '<' && *str != '>'))
		return (parse_quotes(ptr_str, str, start_tok, end_tok));
	if (start_tok)
		*start_tok = str;
	ret = special_chars(&str);
	if (ret != 'a')
		str ++;
	while (*str && !is_whitespace(*str) && *str != '|' && *str != '>'
		&& *str != '<' && ret == 'a')
		str ++;
	if (end_tok)
		*end_tok = str;
	*ptr_str = str;
	return (ret);
}

int	deal_token(t_cmd *cmd, char **str, t_token *token, t_shell *shell)
{
	int		tok_type;
	int		len;
	char	*tmp;

	if (!str || !*str || !**str)
		return (0);
	tok_type = get_token(str, &token->start, &token->end);
	if (tok_type == 0)
		return (0);
	if (tok_type != 'a')
		exit(1);
	len = token->end - token->start;
	tmp = ft_strndup(token->start, len);
	if (ft_strncmp(tmp, "\"\"", 2) == 0 && ft_strlen(tmp) == ft_strlen("\"\""))
		cmd->argv[token->argc] = ft_strdup("");
	else if (ft_strncmp(tmp, "\'\'", 2) == 0
		&& ft_strlen(tmp) == ft_strlen("\'\'"))
		cmd->argv[token->argc] = ft_strdup("");
	else if (!ft_strchr(tmp, '"') && !ft_strchr(tmp, '\''))
		cmd->argv[token->argc] = deal_expansion(tmp, shell);
	else
		cmd->argv[token->argc] = clean_token(tmp, shell, TOKEN);
	free (tmp);
	return (1);
}
