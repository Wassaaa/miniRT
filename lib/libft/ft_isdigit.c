/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:40:08 by jtu               #+#    #+#             */
/*   Updated: 2024/08/22 15:56:07 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The isdigit() function tests for a decimal digit character.
 * @param c The character to be checked, represented as an int.
 *          Note that the function expects the character's ASCII value.
 *
 * @return 1 if the character is a decimal digit (0-9).
 *         0 if the character is not a decimal digit.
 */
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
