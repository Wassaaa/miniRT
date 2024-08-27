/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:53 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:15:54 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_bvh	*make_wireframe(t_bvh *shapes_bvh)
{
	t_list	*wireframe;

	wireframe = NULL;
	generate_aabb_lines(shapes_bvh, 0, &wireframe);
	return (bvh(wireframe));
}