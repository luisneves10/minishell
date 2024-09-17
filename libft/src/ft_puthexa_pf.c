/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:25:28 by luibarbo          #+#    #+#             */
/*   Updated: 2024/05/24 10:34:23 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa_lower_pf(unsigned long long n)
{
	int		len;

	auto char base_lower[16] = "0123456789abcdef";
	len = 0;
	if (n < 16)
		len += ft_putchar_pf(base_lower[n]);
	if (n >= 16)
	{
		len += ft_puthexa_lower_pf(n / 16);
		len += ft_puthexa_lower_pf(n % 16);
	}
	return (len);
}

int	ft_puthexa_upper_pf(unsigned long long n)
{
	int		len;

	auto char base_upper[16] = "0123456789ABCDEF";
	len = 0;
	if (n < 16)
		len += ft_putchar_pf(base_upper[n]);
	if (n >= 16)
	{
		len += ft_puthexa_upper_pf(n / 16);
		len += ft_puthexa_upper_pf(n % 16);
	}
	return (len);
}
