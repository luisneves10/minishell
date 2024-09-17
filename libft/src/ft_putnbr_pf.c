/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:25:37 by luibarbo          #+#    #+#             */
/*   Updated: 2024/05/24 10:34:38 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pf(int n)
{
	int			len;
	long long	nb;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		len += ft_putchar_pf('-');
		nb *= -1;
	}
	if (nb < 10)
		len += ft_putchar_pf(nb + '0');
	else
	{
		len += ft_putnbr_pf(nb / 10);
		len += ft_putchar_pf(nb % 10 + '0');
	}
	return (len);
}
