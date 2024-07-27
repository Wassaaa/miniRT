#include <miniRT.h>

/*
go throught the array of all the shapes in the current partition
and assign appropriate box around all the objects by adjusting the 
min and max values of the box while going through all the objects in the partition
effectively dragging the box bigger and bigger until all the shapes fit.
*/
t_aabb compute_box(t_shape **shapes, int num_shapes)
{
	t_shape *shape;
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
/*
find the longest axis if a aabb box
vector_substrac max - min gives all the biggest values of the box
abs_value each for safety
return the axis that has the biggest value
could also do abs(box.max.x - box.min.x) for each axis and get the biggest
*/
int	find_longest_axis(t_aabb box)
{
	t_vector dimensions;

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

double	coord_on_axis(t_shape *shape, int axis)
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
Bounding Volume Hierarchy (BVH) system for generating a box around each object
gives us an ability to discard the need for calculation on many rays.
*/
t_bvh *build_bvh(t_shape **shapes, int num_shapes)
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
		shapes[0]->box = node->box;
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
	if (!bvh)
		return (NULL);
	free(shape_array);
	return (bvh);
}

