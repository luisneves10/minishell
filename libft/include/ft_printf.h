/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:14:24 by luibarbo          #+#    #+#             */
/*   Updated: 2024/04/30 11:42:24 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *s, ...);
int	ft_putchar_pf(int c);
int	ft_putstr_pf(char *s);
int	ft_putnbr_pf(int n);
int	ft_putnbr_unsigned_pf(unsigned int n);
int	ft_puthexa_lower_pf(unsigned long long n);
int	ft_puthexa_upper_pf(unsigned long long n);
int	ft_putpointer_pf(unsigned long long n);

#endif
