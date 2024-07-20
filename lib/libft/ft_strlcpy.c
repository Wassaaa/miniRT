/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:39 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 19:03:18 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * strlcpy() copies up to dstsize - 1 characters from the
 * string src to dst, NUL-terminating the result if dstsize
 * is not 0.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = 0;
	return (i);
}
