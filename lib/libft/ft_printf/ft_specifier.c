/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:41:15 by jtu               #+#    #+#             */
/*   Updated: 2023/11/22 13:16:37 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_spec(t_printf *print, const char *fmt)
{
	if (*fmt == 'c')
		return (print_char(print));
	else if (*fmt == 's')
		return (print_str(print));
	else if (*fmt == 'p')
		return (print_ads(print));
	else if (*fmt == 'd' || *fmt == 'i')
		return (print_num(print, DECIMAL, 'd'));
	else if (*fmt == 'u')
		return (print_num(print, DECIMAL, 'u'));
	else if (*fmt == 'x')
		return (print_num(print, HEXALOW, 'x'));
	else if (*fmt == 'X')
		return (print_num(print, HEXAUPP, 'x'));
	else if (*fmt == '%')
	{
		if (ft_putchar('%') != 1)
			return (-1);
		print->len++;
		return (1);
	}
	else
		return (-1);
}

int	print_char(t_printf *print)
{
	char	c;

	c = (char)va_arg(print->args, int);
	if (ft_putchar(c) != 1)
		return (-1);
	print->len++;
	return (1);
}

int	print_str(t_printf *print)
{
	char	*s;

	s = va_arg(print->args, char *);
	if (!s)
	{
		if (ft_putstr("(null)") != 1)
			return (-1);
		print->len += 6;
		return (1);
	}
	if (ft_putstr(s) != 1)
		return (-1);
	print->len += ft_strlen(s);
	return (1);
}

int	print_num(t_printf *print, char *base, char type)
{
	int	nbr;

	if (type == 'd')
		nbr = va_arg(print->args, int);
	else
		nbr = va_arg(print->args, unsigned int);
	if (ft_putnbr_base((long)nbr, base, type) != 1)
		return (-1);
	print->len += ft_numlen_base((long)nbr, base, type);
	return (1);
}

int	print_ads(t_printf *print)
{
	unsigned long	ptr;

	ptr = va_arg(print->args, unsigned long);
	if (ft_putstr("0x") != 1)
		return (-1);
	print->len += 2;
	if (ft_putnbr_base_ul((long)ptr, HEXALOW) != 1)
		return (-1);
	print->len += ft_numlen_base_ul((long)ptr, HEXALOW);
	return (1);
}
