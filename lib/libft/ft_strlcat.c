/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:30:00 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 20:13:01 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * strlcat() appends string src to the end of dst. It
 * will append at most dstsize - strlen(dst) - 1
 * characters.  It will then NUL-terminate, unless
 * dstsize is 0 or the original dst string was
 * longer than dstsize (in practice this should not
 * happen as it means that either dstsize is incorrect
 * or that dst is not a proper string).
 * @param dst - The string to be appended to
 * @param src - The string to append to it
 * @param size - The size of the destination buffer
 * @return strlen(src) + MIN(siz, strlen(initial dst))
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len_dst;
	unsigned int	len_src;

	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src + size);
	len_dst = ft_strlen(dst);
	if (size <= len_dst)
		return (len_src + size);
	i = 0;
	while (src[i] && i < size - len_dst - 1)
	{
		dst[i + len_dst] = src[i];
		i++;
	}
	dst[i + len_dst] = '\0';
	return (len_dst + len_src);
}
