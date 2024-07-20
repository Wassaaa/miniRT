/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:58:40 by jtu               #+#    #+#             */
/*   Updated: 2023/11/22 15:34:22 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialise_list(t_printf *print)
{
	print->len = 0;
}

/**
 * The printf() function writes output to
 * stdout, the standard output stream
 * @return the number of characters printed (not including
 * the trailing `\0' used to end output to strings)
*/
int	ft_printf(const char *fmt, ...)
{
	t_printf	print;

	initialise_list(&print);
	va_start(print.args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			if (convert_spec(&print, ++fmt) != 1)
			{
				va_end(print.args);
				return (-1);
			}
		}
		else if (ft_putchar(*fmt) == 1)
			print.len += 1;
		else
		{
			va_end(print.args);
			return (-1);
		}
		fmt++;
	}
	va_end(print.args);
	return (print.len);
}
