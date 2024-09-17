/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_pf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:07:20 by luibarbo          #+#    #+#             */
/*   Updated: 2024/05/24 10:35:25 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer_pf(unsigned long long n)
{
	int	len;

	if (!n)
		return (ft_putstr_pf("(nil)"));
	len = 0;
	len += ft_putstr_pf("0x");
	len += ft_puthexa_lower_pf(n);
	return (len);
}
