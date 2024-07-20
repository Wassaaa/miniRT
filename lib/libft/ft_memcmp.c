/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:46:20 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:26:39 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The memcmp() function compares byte string s1 against byte
 * string s2.  Both strings are assumed to be n bytes long.
 * @return the difference of two strings.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_char;
	unsigned char	*s2_char;

	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	while (n--)
	{
		if (*s1_char != *s2_char)
			return (*s1_char - *s2_char);
		s1_char++;
		s2_char++;
	}
	return (0);
}
