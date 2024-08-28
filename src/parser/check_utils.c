/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:37 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:26:19 by jtu              ###   ########.fr       */
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

/**
 * Counts occurrences of a character in a string.
 *
 * This function iterates through the string 's' and counts
 * how many times the character 'c' appears.
 *
 * @param s The string to be searched.
 * @param c The character to count (passed as an int, but converted to char).
 *
 * @return The number of times 'c' occurs in 's'. Returns 0 if 's' is NULL
 *         or if 'c' is not found.
 *
 * @note The function treats 'c' as an unsigned char to handle extended ASCII.
 *
 * Visual representation:
 *   Input:  s = "Hello, World!", c = 'l'
 *   Count:     ^       ^  ^
 *              1       2  3
 *   Returns: 3
 */
int	ft_char_count(const char *s, int c)
{
	int				count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == (char)c)
			count++;
		s++;
	}
	return (count);
}
