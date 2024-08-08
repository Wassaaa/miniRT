#include <miniRT.h>


static inline bool	update_hit(t_bvh *node, t_hit *t, t_ray *ray)
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

static inline bool	next_branches(t_bvh *node, t_ray *ray, t_hit *hit)
{
	bool	hit_left;
	bool	hit_right;
	t_hit	right;
	t_hit	left;

	left = (t_hit){INFINITY, NULL, false, VV, VV, NULL};
	right = (t_hit){INFINITY, NULL, false, VV, VV, NULL};
	hit_left = intersect_bvh(node->left, ray, &left);
	hit_right = intersect_bvh(node->right, ray, &right);
	if (hit_left && (!hit_right || left.distance < right.distance))
	{
		*hit = left;
		return (true);
	}
	else if (hit_right)
	{
		*hit = right;
		return (true);
	}
	return (false);
}

bool	intersect_bvh(t_bvh *node, t_ray *ray, t_hit *old_t)
{
	bool	curr_hit;
	t_hit	hit;

	hit = (t_hit){INFINITY, NULL, false, VV, VV, NULL};
	curr_hit = false;

	if (!intersect_aabb(*ray, node->box, hit.distance))
		return (false);
	if (node->shape)
		curr_hit = update_hit(node, &hit, ray);
	else
		curr_hit = next_branches(node, ray, &hit);
	if (curr_hit && hit.distance < old_t->distance)
		*old_t = hit;
	return (curr_hit);
}
