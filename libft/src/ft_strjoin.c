/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:24:50 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/19 17:11:56 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1len;
	int		s2len;
	int		i;

	s1len = 0;
	s2len = 0;
	i = 0;
	while (s1[s1len])
		s1len ++;
	while (s2[s2len])
		s2len ++;
	str = malloc((s1len * sizeof(char)) + (s2len * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	while (i < s1len)
	{
		str[i] = s1[i];
		i ++;
	}
	i = 0;
	while (i < s2len)
		str[s1len++] = s2[i++];
	str[s1len] = '\0';
	return (str);
}
