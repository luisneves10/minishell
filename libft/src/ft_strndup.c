/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:32:33 by luibarbo          #+#    #+#             */
/*   Updated: 2024/10/30 12:39:29 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(char *str, size_t n)
{
	size_t	i;
	size_t	len;
	char	*str2;

	len = 0;
	if (!str)
		return (NULL);
	while (len < n && str[len])
		len ++;
	str2 = ft_calloc(len + 1, sizeof(char));
	if (!str2)
		return (NULL);
	i = 0;
	while (str[i] && i < len)
	{
		str2[i] = str[i];
		i++;
	}
	return (str2);
}
