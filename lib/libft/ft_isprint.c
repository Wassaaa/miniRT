/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:46:07 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:13:21 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The isprint() function tests for any printing character,
 * including space (` ').  The value of the argument must
 * be representable as an unsigned char or the value of EOF.
*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
