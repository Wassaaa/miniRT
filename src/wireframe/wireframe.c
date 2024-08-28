/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:53 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 19:13:53 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wireframe.h>

t_color	wireframe_color(int depth)
{
	static t_color	depth_colors[10];
	static bool		is_initialized = false;

	if (!is_initialized)
	{
		depth_colors[0] = color_from_hex(COLOR_GREEN);
		depth_colors[1] = color_from_hex(COLOR_BLUE);
		depth_colors[2] = color_from_hex(COLOR_RED);
		depth_colors[3] = color_from_hex(COLOR_YELLOW);
		depth_colors[4] = color_from_hex(COLOR_MAGENTA);
		depth_colors[5] = color_from_hex(COLOR_CYAN);
		depth_colors[6] = color_from_hex(COLOR_ORANGE);
		depth_colors[7] = color_from_hex(COLOR_PURPLE);
		depth_colors[8] = color_from_hex(COLOR_LIME);
		depth_colors[9] = color_from_hex(COLOR_GRAY);
		is_initialized = true;
	}
	return (depth_colors[depth % 10]);
}

t_bvh	*make_wireframe(t_bvh *shapes_bvh)
{
	t_list	*wireframe;

	wireframe = NULL;
	generate_aabb_lines(shapes_bvh, 0, &wireframe);
	return (bvh(wireframe));
}
