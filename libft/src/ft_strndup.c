/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:32:33 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/29 15:15:16 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(char *str, size_t n)
{
	size_t		i;
	char		*str2;

	str2 = ft_calloc(n + 1, sizeof(char));
	if (!str2)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		str2[i] = str[i];
		i++;
	}
	return (str2);
}
