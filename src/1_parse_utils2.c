/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:19:00 by luibarbo          #+#    #+#             */
/*   Updated: 2024/11/14 11:10:46 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_argv(char **argv, int size, int i, int j)
{
	char	**new_argv;

	new_argv = ft_calloc(sizeof(char *), size + 1);
	if (!new_argv)
		return (NULL);
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			new_argv[j] = ft_strdup("");
			j ++;
		}
		else if (ft_strncmp(argv[i], EXPAND_NULL, 11) != 0)
		{
			new_argv[j] = ft_strdup(argv[i]);
			if (!new_argv[j])
			{
				perror("ft_strdup");
				return (NULL);
			}
			j++;
		}
		i++;
	}
	return (new_argv);
}

char	**clean_argv(t_cmd *cmd)
{
	int		i;
	int		j;
	int		size;
	char	**new_argv;

	i = 0;
	j = 0;
	size = 0;
	while (cmd->argv[i])
	{
		if (ft_strncmp(cmd->argv[i], EXPAND_NULL, 11) != 0)
			size++;
		i++;
	}
	i = 0;
	new_argv = copy_argv(cmd->argv, size, i, j);
	i = 0;
	while (cmd->argv[i])
		free (cmd->argv[i++]);
	free (cmd->argv);
	return (new_argv);
}

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
		while (is_whitespace(*str) && !in_quotes)
			str++;
		if (*str && !is_whitespace(*str) && *str != '|')
			shell->argc++;
		while (*str && (in_quotes || (!is_whitespace(*str) && *str != '|')))
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

int	find_char(char **ptr_str, char *set)
{
	char	*s;

	if (!ptr_str || !*ptr_str || !set)
		return (0);
	s = *ptr_str;
	if (*s )
	{
		while (*s && is_whitespace(*s))
			s++;
	}
	*ptr_str = s;
	if (*s && ft_strchr(set, *s))
		return (1);
	else
		return (0);
}
