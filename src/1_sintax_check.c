/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sintax_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:59:05 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/10 15:01:58 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_error(char *str)
{
	printf("minishell: %s\n", str);
	return (1);
}

int	check_quotes(char *input)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*input)
	{
		if (*input == '\'')
			single_quotes++;
		if (*input == '"')
			double_quotes++;
		input++;
	}
	if (single_quotes % 2 != 0)
		return (mini_error("sintax error: missing single quotes \'\'\'"));
	if (double_quotes % 2 != 0)
		return (mini_error("sintax error: missing double quotes \'\"\'"));
	return (0);
}

int	check_pipes(char *input)
{
	while (*input == ' ')
		input++;
	if (*input == '|')
		return (mini_error("syntax error near unexpected token `|'"));
	while (*input)
	{
		if (*input == '|')
		{
			input ++;
			while (*input == ' ')
				input++;
			if (*input == '|' || *input == '\0')
				return (mini_error("syntax error near unexpected token `|'"));
		}
		input++;
	}
	return (0);
}

int	check_redirs(char *input)
{
	char	*end_str;

	end_str = &input[ft_strlen(input)];
	while (*input)
	{
		if (*input == '>' || *input == '<' || !ft_strncmp(input, ">>", 2)
			|| !ft_strncmp(input, "<<", 2))
		{
			input++;
			if (*input == '>' || *input == '<')
				input++;
			while (*input == ' ')
				input++;
			if (*input == '\0')
				return (mini_error("syntax error near unexpected token `newline'"));
			if (find_char(&input, end_str, "<>|"))
				return (mini_error("syntax error near unexpected token")); //need to have the token to error??
		}
		input++;
	}
	return (0);
}

int	syntax_check(char *input)
{
	if (check_quotes(input) == 0 && check_pipes(input) == 0
		&& check_redirs(input) == 0)
		return (0);
	return (1);
}
