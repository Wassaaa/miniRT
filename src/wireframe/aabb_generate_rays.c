/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_generate_rays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:43 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:19:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wireframe.h>

static void	set_corners(t_aabb box, t_vector *corners)
{
	corners[0] = (t_vector){box.min.x, box.min.y, box.min.z};
	corners[1] = (t_vector){box.max.x, box.min.y, box.min.z};
	corners[2] = (t_vector){box.min.x, box.max.y, box.min.z};
	corners[3] = (t_vector){box.max.x, box.max.y, box.min.z};
	corners[4] = (t_vector){box.min.x, box.min.y, box.max.z};
	corners[5] = (t_vector){box.max.x, box.min.y, box.max.z};
	corners[6] = (t_vector){box.min.x, box.max.y, box.max.z};
	corners[7] = (t_vector){box.max.x, box.max.y, box.max.z};
}

void	make_aabb_line(t_list **lines, t_vector start,
						t_vector end, int depth)
{
	t_shape	*line;

	line = ft_calloc(1, sizeof(t_shape));
	if (!line)
		return ;
	line->type = WIREFRAME;
	line->pos = start;
	line->color = wireframe_color(depth);
	line->dir = vector_subtract(end, start);
	line->radius = AABB_LINE_THICKNESS * pow(0.8, depth);
	line->diameter = line->radius * 2;
	line->boxfunc = box_line;
	line->box = line->boxfunc(line);
	ft_lstadd_back(lines, ft_lstnew(line));
}

/*
Front Face = first 4
Back Face = middle 4
connecting edges = last 4
*/
static void	add_lines(t_list **lines, t_vector *corners, int depth)
{
	make_aabb_line(lines, corners[0], corners[1], depth);
	make_aabb_line(lines, corners[1], corners[3], depth);
	make_aabb_line(lines, corners[3], corners[2], depth);
	make_aabb_line(lines, corners[2], corners[0], depth);
	make_aabb_line(lines, corners[4], corners[5], depth);
	make_aabb_line(lines, corners[5], corners[7], depth);
	make_aabb_line(lines, corners[7], corners[6], depth);
	make_aabb_line(lines, corners[6], corners[4], depth);
	make_aabb_line(lines, corners[0], corners[4], depth);
	make_aabb_line(lines, corners[1], corners[5], depth);
	make_aabb_line(lines, corners[2], corners[6], depth);
	make_aabb_line(lines, corners[3], corners[7], depth);
}

static void	add_connecting_edges(t_list **lines, t_vector *corners,
				int depth)
{
	make_aabb_line(lines, corners[0], corners[4], depth);
	make_aabb_line(lines, corners[1], corners[5], depth);
	make_aabb_line(lines, corners[2], corners[6], depth);
	make_aabb_line(lines, corners[3], corners[7], depth);
}

/**
 * Recursively generates AABB lines for BVH visualization.
 *
 * Creates color-coded lines representing the AABB of each BVH node.
 * Lines are added to the provided list for later rendering.
 *
 * @param node Current BVH node
 * @param depth Depth in BVH tree (for color coding)
 * @param lines List to store generated lines
 */
void	generate_aabb_lines(t_bvh *node, int depth, t_list **lines)
{
	t_vector	corners[8];

	if (!node)
		return ;
	set_corners(node->box, corners);
	add_lines(lines, corners, depth);
	add_connecting_edges(lines, corners, depth);
	generate_aabb_lines(node->left, depth + 1, lines);
	generate_aabb_lines(node->right, depth + 1, lines);
}
