/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sintax_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:59:05 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/23 15:38:30 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_error(char *str, int error)
{
	printf("minishell: sintax error%s\n", str);
	if (error == S_Q)
		return (S_Q);
	else if (error == D_Q)
		return (D_Q);
	else if (error == ERROR_P)
		return (ERROR_P);
	else if (error == ER_TOK)
		return (ER_TOK);
	else if (error == E_NWL)
		return (E_NWL);
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
		return (mini_error(": missing single quotes \'\'\'", S_Q));
	if (double_quotes % 2 != 0)
		return (mini_error(": missing double quotes \'\"\'", D_Q));
	return (0);
}

int	check_pipes(char *input)
{
	while (*input == ' ')
		input++;
	if (*input == '|')
		return (mini_error(" near unexpected token `|'", ERROR_P));
	while (*input)
	{
		if (*input == '|')
		{
			input ++;
			while (*input == ' ')
				input++;
			if (*input == '|' || *input == '\0')
				return (mini_error(" near unexpected token `|'", 43));
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
				return (mini_error(" near unexpected token `newline'", E_NWL));
			if (find_char(&input, end_str, "<>|"))
				return (mini_error(" near unexpected token", ER_TOK)); //need to have the token to error??
		}
		input++;
	}
	return (0);
}

int	syntax_check(t_shell *shell)
{
	token_count(shell->input, shell);
	if (check_quotes(shell->input) == 0 && check_pipes(shell->input) == 0
		&& check_redirs(shell->input) == 0)
		return (0);
	return (1);
}
