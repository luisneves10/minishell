/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_pf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:04:09 by luibarbo          #+#    #+#             */
/*   Updated: 2024/05/24 10:35:04 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned_pf(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 10)
		len += ft_putchar_pf(n + '0');
	else
	{
		len += ft_putnbr_unsigned_pf(n / 10);
		len += ft_putnbr_unsigned_pf(n % 10);
	}
	return (len);
}
