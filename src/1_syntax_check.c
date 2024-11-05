/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_syntax_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:59:05 by daduarte          #+#    #+#             */
/*   Updated: 2024/11/05 15:46:36 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_error(char *str, int error, t_shell *shell)
{
	shell->exit_status = error;
	if (error == -1)
	{
		shell->exit_status = 1;
		printf("minishell: %s", str);
		return (-1);
	}
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

void	on_off_flag(int *flag)
{
	if (*flag == 1)
		*flag = 0;
	else if (*flag == 0)
		*flag = 1;
}

int	check_closed_quotes(char **input, char *quote_type, t_shell *shell)
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
			return (mini_error(": missing single quotes \'\'\'", S_Q, shell));
		if (*quote_type == '"')
			return (mini_error(": missing double quotes \'\"\'", D_Q, shell));
	}
	return (0);
}

int	check_chars_and_quotes(t_shell *shell)
{
	char	quote_type;
	int		ret;
	char	*input;

	input = shell->input;
	quote_type = '\0';
	ret = 0;
	while (*input)
	{
		while (*input && *input != '"' && *input != '\'')
		{
			if (ft_strchr("\\;()&!*", *input))
				return (mini_error(": invalid character", INV_CHAR, shell));
			input++;
		}
		if (*input && (*input == '\'' || *input == '"'))
		{
			ret = check_closed_quotes(&input, &quote_type, shell);
			if (ret)
				return (ret);
		}
	}
	return (0);
}

int	check_pipes(t_shell *shell)
{
	char	*input;
	int		flag;

	flag = 0;
	input = shell->input;
	while (*input == ' ')
		input++;
	if (*input == '|')
		return (mini_error(" near unexpected token `|'", ERROR_P, shell));
	while (*input)
	{
		if (*input == '"' || *input == '\'')
			on_off_flag(&flag);
		if (*input == '|')
		{
			input ++;
			while (*input == ' ')
				input++;
			if ((*input == '|' && flag == 0)|| *input == '\0')
				return (mini_error(" near unexpected token `|'", 43, shell));
		}
		if (*input != '"' || *input != '\'')
			input++;
	}
	return (0);
}

int	check_redirs(t_shell *shell)
{
	char	*input;
	int		flag;

	flag = 0;
	input = shell->input;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
			on_off_flag(&flag);
		if (*input == '>' || *input == '<' || !ft_strncmp(input, ">>", 2)
			|| !ft_strncmp(input, "<<", 2))
		{
			input++;
			if (*input == '>' || *input == '<')
				input++;
			while (*input == ' ')
				input++;
			if (*input == '\0')
				return (mini_error(" near unexpected token `newline'", E_NWL, shell));
			if (find_char(&input, "<>|") && flag == 0)
				return (mini_error(" near unexpected token", ER_TOK, shell));
		}
		input++;
	}
	return (0);
}


int	syntax_check(t_shell *shell)
{
	if (check_chars_and_quotes(shell) == 0
		&& check_pipes(shell) == 0 && check_redirs(shell) == 0)
		return (0);
	return (1);
}
