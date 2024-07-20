/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:41:03 by jtu               #+#    #+#             */
/*   Updated: 2023/11/22 14:38:28 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	while (*s)
	{
		if (ft_putchar(*s) < 0)
			return (-1);
		s++;
	}
	return (1);
}

int	ft_putnbr_base(long nbr, char *base, char type)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (nbr < 0 && type == 'd')
	{
		if (ft_putchar('-') != 1)
			return (-1);
		nbr = -nbr;
	}
	else
		nbr = (unsigned int) nbr;
	if (nbr >= base_len)
	{
		if (ft_putnbr_base(nbr / base_len, base, type) != 1)
			return (-1);
		if (ft_putnbr_base(nbr % base_len, base, type) != 1)
			return (-1);
	}
	else
		if (write(1, (base + nbr), 1) != 1)
			return (-1);
	return (1);
}

int	ft_putnbr_base_ul(unsigned long nbr, char *base)
{
	unsigned long	base_len;

	base_len = ft_strlen(base);
	if (nbr >= base_len)
	{
		if (ft_putnbr_base_ul(nbr / base_len, base) != 1)
			return (-1);
		if (ft_putnbr_base_ul(nbr % base_len, base) != 1)
			return (-1);
	}
	else
		if (write(1, (base + nbr), 1) != 1)
			return (-1);
	return (1);
}
