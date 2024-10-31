/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_syntax_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:59:05 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/31 14:47:59 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_error(char *str, int error)
{
	printf("minishell: syntax error%s\n", str);
	if (error == INV_CHAR)
		return (INV_CHAR);
	else if (error == S_Q)
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

int	check_closed_quotes(char **input, char *quote_type)
{
	*quote_type = **input;
	(*input)++;
	while (**input && **input != *quote_type)
		(*input)++;
	if (**input && **input == *quote_type)
	{
		(*input)++;
		return (0);
	}
	if (!(**input))
	{
		if (*quote_type == '\'')
			return (mini_error(": missing single quotes \'\'\'", S_Q));
		if (*quote_type == '"')
			return (mini_error(": missing double quotes \'\"\'", D_Q));
	}
	return (0);
}

int	check_chars_and_quotes(char *input)
{
	char	quote_type;
	int		ret;

	quote_type = '\0';
	ret = 0;
	while (*input)
	{
		while (*input && *input != '"' && *input != '\'')
		{
			if (ft_strchr("\\;()&!*", *input))
				return (mini_error(": invalid character", INV_CHAR));
			input++;
		}
		if (*input && (*input == '\'' || *input == '"'))
		{
			ret = check_closed_quotes(&input, &quote_type);
			if (ret)
				return (ret);
		}
	}
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
			if (find_char(&input, "<>|"))
				return (mini_error(" near unexpected token", ER_TOK)); //need to have the token to error??
		}
		input++;
	}
	return (0);
}

int	syntax_check(t_shell *shell)
{
	if (check_chars_and_quotes(shell->input) == 0
		&& check_pipes(shell->input) == 0 && check_redirs(shell->input) == 0)
		return (0);
	return (1);
}
