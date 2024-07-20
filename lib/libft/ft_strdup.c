/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:38:34 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:35:25 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strdup() function allocates sufficient memory for a
 * copy of the string s1, does the copy, and returns a
 * pointer to it. The pointer may subsequently be used as
 * an argument to the function free(3).
 */
char	*ft_strdup(const char *src)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(src);
	ptr = (char *) malloc ((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, src, len + 1);
	return (ptr);
}
