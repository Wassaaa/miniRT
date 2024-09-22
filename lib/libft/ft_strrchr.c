/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:47:18 by jtu               #+#    #+#             */
/*   Updated: 2024/09/22 14:22:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strrchr() function returns a pointer to the last
 * occurrence of the character c in the string s.
 * @param s The string to be searched.
 * @param c The character to search for (passed as an int,
 * but converted to char).
 *
 * @return If the character is found, returns a pointer to the last occurrence
 *         of the character in the string. If the character is not found,
 *         returns NULL. If 'c' is the null terminator, returns a pointer to
 *         the null terminator of the string
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if ((char)c == s[i])
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
