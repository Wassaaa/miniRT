/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:44:40 by jtu               #+#    #+#             */
/*   Updated: 2024/04/03 15:41:07 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates (with malloc(3)) and returns a substring
 * from the string ’s’.
 * The substring begins at index ’start’ and is of
 * maximum size ’len’.
 * @param s - The string from which to create the substring.
 * @param start - The start index of the substring in the
 * string ’s’.
 * @param len - The maximum length of the substring.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_s = malloc(len * sizeof(char) + 1);
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len && i + start < ft_strlen(s))
	{
		sub_s[i] = s[i + start];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
