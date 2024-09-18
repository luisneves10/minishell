/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:16:13 by luibarbo          #+#    #+#             */
/*   Updated: 2024/06/19 09:48:23 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*bufs;
	t_list			*tmp;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		while (bufs)
		{
			tmp = bufs->next;
			free (bufs->content);
			free (bufs);
			bufs = tmp;
		}
		bufs = NULL;
		return (NULL);
	}
	get_bufs(&bufs, fd);
	if (!bufs)
		return (NULL);
	line = get_line(bufs);
	start_next_list(&bufs);
	return (line);
}

void	get_bufs(t_list **bufs, int fd)
{
	int		chars_read;
	char	*buf;

	if (!bufs)
		return ;
	while (!find_nl(*bufs))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read < 1)
		{
			free (buf);
			return ;
		}
		buf[chars_read] = '\0';
		lst_add_back(bufs, buf);
	}
}

void	lst_add_back(t_list **lst, char *str)
{
	t_list	*new;
	t_list	*last;

	last = lst_last(*lst);
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	if (!last)
		*lst = new;
	else
		last->next = new;
	new->content = str;
	new->next = NULL;
}

char	*get_line(t_list *lst)
{
	int		len;
	char	*str;

	if (!lst)
		return (NULL);
	len = line_len(lst);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	create_string(lst, str);
	return (str);
}

void	start_next_list(t_list **lst)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
	last = lst_last(*lst);
	i = 0;
	j = 0;
	while (last->content[i] && last->content[i] != '\n')
		++i;
	while (last->content[i] && last->content[++i])
		buf[j++] = last->content[i];
	buf[j] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	clean_used_list(lst, clean_node, buf);
}
