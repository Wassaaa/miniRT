/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:45:43 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:13:54 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The isalpha() function tests for any character for which
 * isupper(3) or islower(3) is true. The value of the
 * argument must be representable as an unsigned char or the
 * value of EOF.
 */
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
