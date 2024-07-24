#include <miniRT.h>

t_vector	vector_min(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = fmin(a.x, b.x);
	result.y = fmin(a.y, b.y);
	result.z = fmin(a.z, b.z);
	return (result);
}

t_vector	vector_max(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = fmax(a.x, b.x);
	result.y = fmax(a.y, b.y);
	result.z = fmax(a.z, b.z);
	return (result);
}

/*
Axis-Aligned Bounding Boxes (AABB)
find the aabb box that can be drawn around a sphere shape
radius_vector represents the distance from the center of the sphere
to any corner of its bounding box in 3D space.
By adding or subtracting this vector from the center,
we reach the corners of the bounding box.
then we compare the new box values with the incoming box and
update the values if needed
*/
void	box_sphere(t_shape sphere, t_aabb *box)
{
	t_vector	radius_vec;
	t_aabb		sphere_box;

	radius_vec = (t_vector){sphere.radius, sphere.radius, sphere.radius};
	sphere_box.min = vector_subtract(sphere.pos, radius_vec);
	sphere_box.max = vector_add(sphere.pos, radius_vec);
	box->max = vector_max(box->max, sphere_box.max);
	box->min = vector_min(box->min, sphere_box.min);
}

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

	end_box.min = (t_vector){DBL_MAX, DBL_MAX, DBL_MAX};
	end_box.max = (t_vector){DBL_MIN, DBL_MIN, DBL_MIN};
	i = 0;
	while (i < num_shapes)
	{
		shape = shapes[i];
		if (shape->type == SPHERE)
			box_sphere(*shape, &end_box);
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
		while (coord_on_axis(shapes[i], axis) < median)
			i++;
		while (coord_on_axis(shapes[j], axis) >= median)
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
	node->box = compute_box(shapes, num_shapes);
	node->id = rtx()->bvh_node_id++;
	if (num_shapes == 1)
	{
		node->shape = shapes[0];
		return (node);
	}
	split_axis = find_longest_axis(node->box);
	split_index = partition_shapes(shapes, num_shapes, split_axis);
	if (split_index == 0 || split_index == num_shapes)
		split_index = num_shapes / 2;
	node->left = build_bvh(shapes, split_index);
	node->right = build_bvh(shapes + split_index, num_shapes - split_index);
	return (node);
}

void	bvh(t_list *shapes)
{
	int		num_shapes;
	t_shape	**shape_array;
	int		i;

	num_shapes = ft_lstsize(shapes);
	shape_array = ft_calloc(num_shapes, sizeof(t_shape *));
	i = 0;
	while (shapes)
	{
		shape_array[i++] = (t_shape *)shapes->content;
		shapes = shapes->next;
	}
	rtx()->bvh = build_bvh(shape_array, num_shapes);
	free(shape_array);
}

bool	update_hit(t_bvh *node, t_intersection *t, t_ray ray)
{
	double	current_t;

	if (intersect(node->shape, ray, &current_t))
	{
		if (current_t < t->distance)
		{
			t->shape = node->shape;
			t->distance = current_t;
			t->hit = true;
			return (true);
		}
	}
	return (false);
}

bool	next_branches(t_bvh *node, t_ray ray, t_intersection *t)
{
	bool	hit_left;
	bool	hit_right;
	t_intersection	right;
	t_intersection	left;

	left = (t_intersection){INFINITY, NULL, false};
	right = (t_intersection){INFINITY, NULL, false};
	hit_left = intersect_bvh(node->left, ray, &left);
	hit_right = intersect_bvh(node->right, ray, &right);
	if (hit_left && (!hit_right || left.distance < right.distance))
	{
		*t = left;
		return (true);
	}
	else if (hit_right)
	{
		*t = right;
		return (true);
	}
	return (false);
}

bool	intersect_bvh(t_bvh *node, t_ray ray, t_intersection *t)
{
	bool	cached;
	bool	hit;

	cached = bvh_cache_check(rtx()->bvh_cache, node->id);
	if (cached)
	{
		rtx()->cache_hits++;
		if (node->shape)
			return (update_hit(node, t, ray));
		else
			return (next_branches(node, ray, t));
	}
	if (!intersect_aabb(ray, node->box, t->distance))
	{
		bvh_cache_update(rtx()->bvh_cache, node->id, false);
		return (false);
	}
	if (node->shape)
		hit = update_hit(node, t, ray);
	else
		hit = next_branches(node, ray, t);
	bvh_cache_update(rtx()->bvh_cache, node->id, hit);
	return (hit);
}
