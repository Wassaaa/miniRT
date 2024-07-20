/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:53:41 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:17:03 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Takes as a parameter a node and frees the memory of
 * the node’s content using the function ’del’ given
 * as a parameter and free the node. The memory of
 * ’next’ must not be freed.
 * @param lst - The node to free.
 * @param del - The address of the function used to delete
 * the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
