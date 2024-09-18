/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:13:27 by luibarbo          #+#    #+#             */
/*   Updated: 2024/05/24 10:33:48 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_specifiers(va_list ap, const char specifier);

int	ft_printf(const char *s, ...)
{
	va_list	ap;

	auto int count = 0, i = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			count += ft_specifiers(ap, s[i]);
		}
		else
			count += ft_putchar_pf(s[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

static int	ft_specifiers(va_list ap, const char specifier)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count = ft_putchar_pf(va_arg(ap, int));
	else if (specifier == 's')
		count = ft_putstr_pf(va_arg(ap, char *));
	else if (specifier == 'p')
		count = ft_putpointer_pf(va_arg(ap, unsigned long long));
	else if (specifier == 'd' || specifier == 'i')
		count = ft_putnbr_pf(va_arg(ap, int));
	else if (specifier == 'u')
		count = ft_putnbr_unsigned_pf(va_arg(ap, unsigned int));
	else if (specifier == 'x')
		count = ft_puthexa_lower_pf(va_arg(ap, unsigned int));
	else if (specifier == 'X')
		count = ft_puthexa_upper_pf(va_arg(ap, unsigned int));
	else if (specifier == '%')
		count = ft_putchar_pf('%');
	return (count);
}
