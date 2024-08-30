/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:30 by jtu               #+#    #+#             */
/*   Updated: 2024/08/30 18:09:20 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
find the longest axis if a aabb box
vector_substrac max - min gives all the biggest values of the box
abs_value each for safety
return the axis that has the biggest value
could also do abs(box.max.x - box.min.x) for each axis and get the biggest
*/
static int	find_longest_axis(t_aabb box)
{
	t_vector	dimensions;

	dimensions = vector_subtract(box.max, box.min);
	dimensions.x = fabs(dimensions.x);
	dimensions.y = fabs(dimensions.y);
	dimensions.z = fabs(dimensions.z);
	if (dimensions.x >= dimensions.y && dimensions.x >= dimensions.z)
		return (AXIS_X);
	if (dimensions.y >= dimensions.x && dimensions.y >= dimensions.z)
		return (AXIS_Y);
	return (AXIS_Z);
}

/*
Bounding Volume Hierarchy (BVH) system for generating a box around each object
gives us an ability to discard the need for calculation on many rays.
*/
t_bvh	*build_bvh(t_shape **shapes, int num_shapes)
{
	t_bvh	*node;
	int		split_axis;
	int		split_index;

	node = ft_calloc(1, sizeof(t_bvh));
	if (!node)
		return (NULL);
	node->id = rtx()->bvh_node_id++;
	if (num_shapes == 1)
	{
		node->box = shapes[0]->box;
		node->shape = shapes[0];
		return (node);
	}
	node->box = compute_box(shapes, num_shapes);
	split_axis = find_longest_axis(node->box);
	split_index = partition_shapes(shapes, num_shapes, split_axis);
	if (split_index == 0 || split_index == num_shapes)
		split_index = num_shapes / 2;
	node->left = build_bvh(shapes, split_index);
	node->right = build_bvh(shapes + split_index, num_shapes - split_index);
	return (node);
}

void	free_bvh(t_bvh **bvh)
{
	if (!bvh || !*bvh)
		return ;
	free_bvh(&(*bvh)->left);
	free_bvh(&(*bvh)->right);
	free(*bvh);
	*bvh = NULL;
}

t_bvh	*bvh(t_list *shapes)
{
	t_shape	**shape_array;
	int		num_shapes;
	t_bvh	*bvh;

	rtx()->bvh_node_id = 0;
	if (!shapes)
		return (NULL);
	num_shapes = ft_lstsize(shapes);
	shape_array = shapes_to_arr(shapes, num_shapes);
	if (!shape_array)
		return (NULL);
	bvh = build_bvh(shape_array, num_shapes);
	free(shape_array);
	return (bvh);
}
