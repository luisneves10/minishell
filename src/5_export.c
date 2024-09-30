/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:21:52 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/30 17:20:02 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_options(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			printf("export: No options are allowed.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static void	handle_args(char **argv)
{
	int		i;
	char	*arg;
	char	*equal;
	char	*var_name;
	char	*var_value;

	i = 1;
	while (argv[i] != NULL)
	{
		arg = argv[i];
		equal = ft_strchr(arg, '=');
		if (equal)
		{
			*equal = '\0';
			var_name = arg;
			var_value = equal + 1;
			// funcao tipo setenv
		}
		else
			//funcao tipo setenv com value vazio
		i++;
	}
}

void ft_export(char **argv, char *envp[])
{
	int	j;

	j = 0;
	if (argv[1] == NULL)
	{
		while (envp[j])
			printf("declare -x %s\n", envp[j++]);
		return;
	}
	if (has_options(argv))
		return;
	handle_args(argv);
}
