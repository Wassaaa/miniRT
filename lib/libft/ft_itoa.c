/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:47:00 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 20:16:55 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/**
 * Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
 */
char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*str;
	int		i;

	nbr = n;
	len = count_len(nbr);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	i = len - 1;
	while (i >= 0 && nbr >= 0)
	{
		str[i--] = nbr % 10 + '0';
		nbr /= 10;
		if (nbr == 0)
			break ;
	}
	return (str);
}
