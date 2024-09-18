/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:58:25 by luibarbo          #+#    #+#             */
/*   Updated: 2024/06/06 16:20:19 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*scopy;

	i = 0;
	while (s[i])
		i++;
	scopy = (char *)malloc(sizeof(char) * (i + 1));
	if (scopy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		scopy[i] = s[i];
		i++;
	}
	scopy[i] = '\0';
	return (scopy);
}
