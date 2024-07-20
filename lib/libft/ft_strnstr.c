/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:47:10 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 19:07:49 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strnstr() function locates the first occurrence of
 * the null-terminated string needle in the string haystack,
 * where not more than len characters are searched. Characters
 * that appear after a `\0' character are not searched.
 * @param haystack - The string to be searched
 * @param needle - The string to search for
 * @param len - The maximum number of characters to search
 * @return If needle is an empty string, haystack is returned;
 * if needle occurs nowhere in haystack, NULL is returned;
 * otherwise a pointer to the first character of the first
 * occurrence of needle is returned.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	while (*haystack && len--)
	{
		i = 0;
		while (*(haystack + i) == *(needle + i) && i <= len \
		&& *(haystack + i) && *(needle + i))
			i++;
		if (*(needle + i) == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
