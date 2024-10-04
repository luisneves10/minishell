/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sintax_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:59:05 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/04 16:52:49 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_error(char *str)
{
	printf("minishell: %s\n", str);
	exit(0);
}

void	check_quotes (char *input)
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
		mini_error("sintax error: single quotes \'\'\'");
	if (double_quotes % 2 != 0)
		mini_error("sintax error: single quotes \'\"\'");
}

void	check_pipes (char *input)
{
	while (*input == ' ')
		input++;
	if (*input == '|')
		mini_error("syntax error near unexpected token `|'");
	while (*input)
	{
		if (*input == '|')
		{
			while (*input == ' ')
				input++;
			if (*input == '|' || *input == '\0')
				mini_error("syntax error near unexpected token `|'");
		}
		input++;
	}
}

void	check_redirs (char *input)
{
	char	*end_str;

	end_str = &input[ft_strlen(input)];
	while (*input)
	{
		if (*input == '>' || *input == '<' || ft_strncmp(input, ">>", 2)
			|| ft_strncmp(input, "<<", 2))
		{
			input++;
			if (*input == '>' || *input == '<')
				input++;
			while (*input == ' ')
				input++;
			if (*input == '\0')
				mini_error("syntax error near unexpected token `newline'");
			if (find_char(&input, end_str, "<>|"))
				mini_error("syntax error near unexpected token"); //need to have the token to error??
		}
		input++;
	}
}

void	syntax_check(char *input)
{
	check_quotes(input);
	check_pipes(input);
	check_redirs(input);
}
