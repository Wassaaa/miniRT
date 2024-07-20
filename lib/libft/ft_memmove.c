/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:13 by jtu               #+#    #+#             */
/*   Updated: 2024/03/26 09:58:30 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The memmove() function copies len bytes from string src
 * to string dst.  The two strings may overlap; the copy is
 * always done in a non-destructive manner.
  * @return the original value of dst.
 */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst2 == src2 || n == 0)
		return (dst);
	else if (dst2 < src2)
		ft_memcpy(dst2, src2, n);
	else
	{
		while (n-- > 0)
		{
			dst2[n] = src2[n];
		}
	}
	return (dst);
}
