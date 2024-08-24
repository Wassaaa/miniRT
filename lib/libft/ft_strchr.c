/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:46:51 by jtu               #+#    #+#             */
/*   Updated: 2024/08/24 15:11:59 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strchr() function locates the first occurrence of c
 * (converted to a char) in the string pointed to by s. The
 * terminating null character is considered to be part of
 * the string; therefore if c is `\0', the functions locate
 * the terminating `\0'.
 * @param s - This is the C string to be scanned.
 * @param c - This is the character to be searched in str.
 * @return If the character is found, returns a pointer to the first occurrence
 *         of the character in the string. If the character is not found and
 *         is not the null terminator, returns NULL. If 'c' is the null
 *         terminator, returns a pointer to the null terminator of the string.
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((char)c == *s)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}
