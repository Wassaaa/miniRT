/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:44:56 by jtu               #+#    #+#             */
/*   Updated: 2023/11/20 20:43:55 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The calloc() function contiguously allocates enough space
 * for count objects that are size bytes of memory each and
 * returns a pointer to the allocated memory.  The allocated
 * memory is filled with bytes of value zero.
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	all;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	all = count * size;
	memory = malloc(all);
	if (!memory)
		return (NULL);
	ft_memset(memory, 0, all);
	return (memory);
}
