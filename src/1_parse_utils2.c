/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:19:00 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/30 14:55:02 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_check(char *str, int *in_quotes, char *quote_type)
{
	if (!(*in_quotes))
	{
		*in_quotes = 1;
		*quote_type = *str;
	}
	else
		*in_quotes = 0;
}

void	token_count(char *str, t_shell *shell)
{
	int		in_quotes;
	char	quote_type;

	in_quotes = 0;
	quote_type = 0;
	while (*str)
	{
		while (*str == ' ' && !in_quotes)
			str++;
		if (*str && *str != ' ' && *str != '|')
			shell->argc++;
		while (*str && (in_quotes || (*str != ' ' && *str != '|')))
		{
			if ((*str == '\'' || *str == '"')
				&& (!in_quotes || *str == quote_type))
				quote_check(str, &in_quotes, &quote_type);
			str++;
		}
		if (*str == '|' && !in_quotes)
			return ;
	}
}

int	special_redirs(char **str)
{
	if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			return ('+');
		}
		(*str)--;
		return ('>');
	}
	else if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			return ('-');
		}
		(*str)--;
		return ('<');
	}
	return ('?');
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

int	find_char(char **ptr_str, char *set)
{
	char	*s;

	if (!ptr_str || !*ptr_str || !set)
		return (0);
	s = *ptr_str;
	if (*s && !ft_strchr(set, ' '))
	{
		while (*s && *s == ' ')
			s++;
	}
	*ptr_str = s;
	if (*s && ft_strchr(set, *s))
		return (1);
	else
		return (0);
}
