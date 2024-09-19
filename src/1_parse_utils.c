/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:19:52 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/19 10:21:31 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gettoken(char **ptr_str, char *end_str, char **start_token, char **end_token)
{
	char	*str;
	int	ret;

	str = *ptr_str;
	while (str < end_str && *str == ' ')
		str ++;
	if (str)
	{
		*start_token = str;
		ret = special_chars(str);
	}
	while (str < end_str && *str != ' ')
	{
		str ++;
	}
	*end_token = str;
	*ptr_str = str;
	return (ret);
}

int	special_chars(char *str)
{
	if (*str == '|')
		return ('|');
	else if (*str == '(')
		return ('(');
	else if (*str == ')')
		return (')');
	else if (*str == ';')
		return (';');
	else if (*str == '<')
		return ('<');
	else if (*str == '>')
	{
		str++;
		if (*str == '>')
			return ('+');
	}
	else if (*str == 0)
		return (0);
	return ('a');
}

void	nulterminate(t_cmd *cmd)
{
	t_execcmd *ecmd;
	t_pipecmd *pcmd;
	int	i;

	i = 0;
	if (cmd == NULL)
		exit(0);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->argv[i])
		{
			*ecmd->end_argv[i] = '\0';
			printf("token %d: %s\n", i, ecmd->argv[i]);
			i ++;
		}
	}
	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
	}
}

int	find_char(char **ptr_str, char *end_str, char *set)
{
	char	*s;

	s = *ptr_str;
	while (s < end_str && strchr(" ", *s))
		s++;
	*ptr_str = s;
	return (*s && strchr(set, *s));
}