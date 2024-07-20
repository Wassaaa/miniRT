/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:15:36 by jtu               #+#    #+#             */
/*   Updated: 2023/11/22 13:16:41 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_numlen_base(long nbr, char *base, char type)
{
	int	len;
	int	base_len;

	if (type != 'd')
		nbr = (unsigned int)nbr;
	base_len = ft_strlen(base);
	len = 0;
	if (nbr < 1)
		len++;
	while (nbr)
	{
		nbr /= base_len;
		len++;
	}
	return (len);
}

int	ft_numlen_base_ul(unsigned long nbr, char *base)
{
	int	len;
	int	base_len;

	base_len = ft_strlen(base);
	len = 0;
	if (nbr < 1)
		len++;
	while (nbr)
	{
		nbr /= base_len;
		len++;
	}
	return (len);
}
