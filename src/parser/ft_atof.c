/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:45 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:38:36 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static double	convert_fractional(const char *str, double value)
{
	double	fraction;
	int		digit_count;

	fraction = 0.1;
	digit_count = 0;
	while (*str >= '0' && *str <= '9' && digit_count < DBL_DIG)
	{
		value += (*str - '0') * fraction;
		fraction *= 0.1;
		str++;
		digit_count++;
	}
	return (value);
}

static double	convert_num(const char *str, double value, int sign)
{
	while (*str >= '0' && *str <= '9')
	{
		if (value > DBL_MAX / 10.0)
		{
			if (sign > 0)
				return (DBL_MAX);
			else
				return (-DBL_MAX);
		}
		value = value * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		value = convert_fractional(str, value);
	}
	return (value);
}

/**
 * The ft_atof() function converts the initial portion of the
 * string pointed to by str to double representation.
*/
double	ft_atof(char *str)
{
	double	value;
	int		sign;

	if (!check_float(str))
		error(E_PARSER, ERR_FLOAT_FORMAT);
	value = 0.0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	value = convert_num(str, value, sign);
	return (sign * value);
}
