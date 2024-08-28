/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:27 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:23:09 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
go throught the array of all the shapes in the current partition
and assign appropriate box around all the objects by adjusting the 
min and max values of the box
while going through all the objects in the partition
effectively dragging the box bigger and bigger until all the shapes fit.
*/
t_aabb	compute_box(t_shape **shapes, int num_shapes)
{
	t_shape	*shape;
	t_aabb	end_box;
	int		i;

	end_box.min = (t_vector){INFINITY, INFINITY, INFINITY};
	end_box.max = (t_vector){-INFINITY, -INFINITY, -INFINITY};
	i = 0;
	while (i < num_shapes)
	{
		shape = shapes[i];
		end_box.min = vector_min(end_box.min, shape->box.min);
		end_box.max = vector_max(end_box.max, shape->box.max);
		i++;
	}
	return (end_box);
}

static double	coord_on_axis(t_shape *shape, int axis)
{
	if (axis == AXIS_X)
		return (shape->pos.x);
	if (axis == AXIS_Y)
		return (shape->pos.y);
	return (shape->pos.z);
}

/*
simple sorting to find the partition point
a point where to split the objects on the longest axis
*/
int	partition_shapes(t_shape **shapes, int num_shapes, int axis)
{
	int		i;
	int		j;
	double	median;
	t_shape	*temp;

	median = coord_on_axis(shapes[num_shapes / 2], axis);
	i = 0;
	j = num_shapes - 1;
	while (i <= j)
	{
		while (i >= 0 && coord_on_axis(shapes[i], axis) < median)
			i++;
		while (j >= 0 && coord_on_axis(shapes[j], axis) >= median)
			j--;
		if (i < j)
		{
			temp = shapes[i];
			shapes[i] = shapes[j];
			shapes[j] = temp;
		}
	}
	return (i);
}

/*
build an array of shapes from shapes list
*/
t_shape	**shapes_to_arr(t_list *shapes, int num_shapes)
{
	t_shape	**shape_array;
	int		i;

	shape_array = ft_calloc(num_shapes, sizeof(t_shape *));
	if (!shape_array)
		return (NULL);
	i = 0;
	while (shapes)
	{
		shape_array[i++] = (t_shape *)shapes->content;
		shapes = shapes->next;
	}
	return (shape_array);
}
