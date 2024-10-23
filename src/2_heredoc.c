/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/10/23 12:07:44 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_delimiter(char *start_tok, char *end_tok)
{
	int		len;
	char	*delimiter;

	len = end_tok - start_tok;
	delimiter = malloc(len + 1);
	if (!delimiter)
		exit(1);
	strncpy(delimiter, start_tok, end_tok - start_tok);//MUDAR STRNCPY
	delimiter[len] = '\0';
	return (delimiter);
}

void	handle_heredoc(void)
{
	int	fd;

	fd = open("heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open error (heredoc)");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 error (input redirection)");
		exit(1);
	}
	close(fd);
}
