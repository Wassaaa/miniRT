/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:27:27 by jtu               #+#    #+#             */
/*   Updated: 2023/11/10 17:05:27 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Deletes and frees the given node and every
 * successor of that node, using the function ’del’
 * and free(3).
 * Finally, the pointer to the list must be set to
 * NULL.
 * @param lst - The address of a pointer to a node.
 * @param del - The address of the function used to
 *              delete the content of the node.
 * @return None
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !(*lst))
		return ;
	ft_lstclear(&((*lst)->next), del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
}
