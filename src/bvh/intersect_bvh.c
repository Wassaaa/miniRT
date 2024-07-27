#include <miniRT.h>


static inline bool	update_hit(t_bvh *node, t_intersection *t, t_ray ray)
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

static inline bool	next_branches(t_bvh *node, t_ray ray, t_intersection *t)
{
	bool	hit_left;
	bool	hit_right;
	t_intersection	right;
	t_intersection	left;

	left = (t_intersection){INFINITY, NULL, false, VV, VV};
	right = (t_intersection){INFINITY, NULL, false, VV, VV};
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

bool	intersect_bvh(t_bvh *node, t_ray ray, t_intersection *old_t)
{
	bool			hit;
	t_intersection	t;

	t = (t_intersection){INFINITY, NULL, false, VV, VV};
	hit = false;

	if (!intersect_aabb(ray, node->box, t.distance))
		return (false);
	if (node->shape)
		hit = update_hit(node, &t, ray);
	else
		hit = next_branches(node, ray, &t);
	if (hit && t.distance < old_t->distance)
		*old_t = t;
	return (hit);
}
