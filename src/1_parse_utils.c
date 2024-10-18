/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:19:52 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/17 16:18:43 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_quotes(char **ptr_str, char *end_str, char **start_tok, char **end_tok)
{
	char	*str;
	int		flag;

	str = *ptr_str;
	str++;
	*start_tok = str;
	flag = 0;
	if (**ptr_str == '"')
		flag = 1;
	while (str < end_str && *str != '"' && flag == 1)
		str++;
	while (str < end_str && *str != '\'' && flag == 0)
		str++;
	//*str = '\0';
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

int	special_chars(char **str)
{
	if (**str == '|')
		return ('|');
	else if (**str == '(')
		return ('(');
	else if (**str == ')')
		return (')');
	else if (**str == ';')
		return (';');
	else if (**str == '<')
		return ('<');
	else if (**str == '>' || **str == '<')
	{
		(*str)++;
		if (**str == '>')
			return ('+');
		if (**str == '<')
			return ('-');
		(*str)--;
		if (**str == '<')
			return ('<');
		return ('>');
	}
	else if (**str == 0)
		return (0);
	return ('a');
}

void	null_terminate(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	int			i;

	i = 0;
	if (cmd == NULL)
		exit(0);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->argv[i])
		{
			*ecmd->end_argv[i] = '\0';
			i ++;
		}
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		null_terminate(pcmd->left);
		null_terminate(pcmd->right);
	}
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
