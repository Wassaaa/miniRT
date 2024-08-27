/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:37 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 13:53:06 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	check_range_int(int value, int min, int max, char *err_msg)
{
	if (value < min || value > max)
		error(E_PARSER, err_msg);
}

void	check_range_double(double value, double min, double max, char *err_msg)
{
	if (value < min || value > max)
		error(E_PARSER, err_msg);
}

int	check_float(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
		return (0);
	return (1);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
