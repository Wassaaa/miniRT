/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:54:18 by jtu               #+#    #+#             */
/*   Updated: 2023/11/15 16:19:29 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_num(const char *str, long value, int sign)
{
	while (*str >= 48 && *str <= 57)
	{
		if (value > LONG_MAX / 10)
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
		value *= 10;
		if (value > LONG_MAX - (*str - '0'))
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
		value += *str - '0';
		str++;
	}
	return (value);
}

/**
 * The atoi() function converts the initial portion of the
 * string pointed to by str to int representation.
*/
int	ft_atoi(const char *str)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str ++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	value = convert_num(str, value, sign);
	return (sign * value);
}
