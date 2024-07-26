/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:25:09 by jtu               #+#    #+#             */
/*   Updated: 2024/07/26 23:38:45 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Outputs the string ’s’ to the given file descriptor.
 * @param s - The string to output.
 * @param fd - The file descriptor on which to write.
 */
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		if (!write(fd, s, 1))
			return ;
		s++;
	}
}
