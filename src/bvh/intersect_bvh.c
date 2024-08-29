/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_bvh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:33 by jtu               #+#    #+#             */
/*   Updated: 2024/08/30 01:52:17 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static inline bool	update_hit(t_bvh *node, t_hit *hit, t_ray *ray)
{
	double	current_t;

	if (intersect(node->shape, ray, &current_t))
	{
		if (current_t < hit->t)
		{
			hit->shape = node->shape;
			hit->t = current_t;
			hit->hit = true;
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

	left = new_hit();
	right = new_hit();
	hit_left = intersect_bvh(node->left, ray, &left);
	hit_right = intersect_bvh(node->right, ray, &right);
	if (hit_left && (!hit_right || left.t < right.t))
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

bool	intersect_bvh(t_bvh *node, t_ray *ray, t_hit *old_hit)
{
	bool	curr_hit;
	t_hit	hit;

	hit = new_hit();
	curr_hit = false;
	if (!node)
		return (false);
	if (!intersect_aabb(*ray, node->box, hit.t))
		return (false);
	if (node->shape)
		curr_hit = update_hit(node, &hit, ray);
	else
		curr_hit = next_branches(node, ray, &hit);
	if (curr_hit && hit.t < old_hit->t)
		*old_hit = hit;
	return (curr_hit);
}
