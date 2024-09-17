/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:59:55 by luibarbo          #+#    #+#             */
/*   Updated: 2024/06/06 16:18:14 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*intexceptions(int n)
{
	char	*s;

	if (n == -2147483648)
		s = ft_strdup("-2147483648");
	else
		s = ft_strdup("0");
	return (s);
}

static int	int_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*str_create(int n)
{
	char	*s;
	int		i;
	int		neg;

	neg = 0;
	i = 0;
	s = (char *)malloc(sizeof(char) * (int_len(n) + 1));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	while (n != 0)
	{
		s[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (neg == 1)
		s[i++] = '-';
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (n == -2147483648 || n == 0)
		str = intexceptions(n);
	else
	{
		str = (char *)malloc(sizeof(char) * (int_len(n) + 1));
		if (!str)
			return (NULL);
		tmp = str_create(n);
		j = ft_strlen(tmp) - 1;
		while (j >= 0)
		{
			str[i] = tmp[j];
			i++;
			j--;
		}
		str[i] = '\0';
		free (tmp);
	}
	return (str);
}
