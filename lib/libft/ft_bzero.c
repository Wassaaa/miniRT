/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:45:21 by jtu               #+#    #+#             */
/*   Updated: 2023/11/13 11:41:17 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The bzero() function writes n zeroed bytes to
 * the string s. If n is zero, bzero() does nothing.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
