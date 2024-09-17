/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:45:45 by luibarbo          #+#    #+#             */
/*   Updated: 2024/06/06 16:20:56 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		i;
	int		start;
	int		end;

	start = 0;
	while (s1[start] && check_char(s1[start], set))
		start++;
	end = ft_strlen((char *)s1) - 1;
	while (start < end && check_char(s1[end], set))
		end--;
	s2 = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!s2)
		return (NULL);
	i = 0;
	while (start <= end)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}
