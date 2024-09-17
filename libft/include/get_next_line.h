/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:17:25 by luibarbo          #+#    #+#             */
/*   Updated: 2024/06/19 09:48:46 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	get_bufs(t_list **bufs, int fd);
void	lst_add_back(t_list **lst, char *str);
char	*get_line(t_list *bufs);
void	start_next_list(t_list **lst);

/*---------- UTILS ----------*/

t_list	*lst_last(t_list *lst);
int		find_nl(t_list *lst);
int		line_len(t_list *lst);
void	create_string(t_list *lst, char *str);
void	clean_used_list(t_list **lst, t_list *clean_node, char *content);

#endif
