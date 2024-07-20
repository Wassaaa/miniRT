/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:47:29 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:14:01 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The isascii() function tests for an ASCII character, which
 * is any character between 0 and octal 0177 inclusive.
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
