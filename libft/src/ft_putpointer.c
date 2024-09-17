/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:07:20 by luibarbo          #+#    #+#             */
/*   Updated: 2024/05/23 17:03:13 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(unsigned long long n)
{
	int	len;

	if (!n)
		return (ft_putstr_pf("(nil)"));
	len = 0;
	len += ft_putstr_pf("0x");
	len += ft_putnbr_base(n, "0123456789abcdef");
	return (len);
}
