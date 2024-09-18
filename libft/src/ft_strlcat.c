/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:13:41 by luibarbo          #+#    #+#             */
/*   Updated: 2024/06/06 16:20:31 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = 0;
	dstlen = 0;
	while (dst[dstlen])
		dstlen++;
	if (dstlen < size)
	{
		while (src[srclen] && (dstlen < size - 1 - srclen))
		{
			dst[dstlen + srclen] = src[srclen];
			srclen++;
		}
		dst[dstlen + srclen] = '\0';
	}
	while (src[srclen])
		srclen++;
	if (dstlen >= size)
		dstlen = size;
	return (dstlen + srclen);
}
