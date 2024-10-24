/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:19:00 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/24 12:55:50 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_count(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<')
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
			return ;
		if (str[i] && str[i] != ' ')
			shell->argc++;
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '"' && str[i] != '\'')
				i++;
			i++;
		}
		if (str[i] && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
			return ;
		while (str[i] && str[i] != ' ')
			i++;
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

int	find_char(char **ptr_str, char *end_str, char *set)
{
	char	*s;

	s = *ptr_str;
	while (s < end_str && *s == ' ')
		s++;
	*ptr_str = s;
	if (s < end_str && ft_strchr(set, *s))
		return (1);
	else
		return (0);
}
