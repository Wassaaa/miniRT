/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:41:01 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 15:31:41 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_list	**allocs(void)
{
	static t_list	*allocs = NULL;

	return (&allocs);
}

void	clear_lal(void)
{
	t_list	**lalloc;

	lalloc = allocs();
	ft_lstclear(lalloc, free_content);
}

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free_one_lal(*ptr);
		*ptr = NULL;
	}
}
