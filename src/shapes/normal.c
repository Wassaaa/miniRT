/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:46 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:46:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
** Calculates the normal vector for a cylinder hit point:
** - For caps: normal is cylinder axis (or its inverse)
** - For curved surface: normal points from axis
** - (at the height of the hit) to hit point
*/
t_vector	cylinder_normal(t_hit *hit)
{
	t_shape		*shape;
	double		hit_height;
	t_vector	axis_point;
	t_vector	normal;

	shape = hit->shape;
	hit_height = vector_dot(
			vector_subtract(hit->hit_point, shape->pos), shape->dir);
	if (fabs(hit_height - shape->half_height) < EPSILON)
		normal = shape->dir;
	else if (fabs(hit_height + shape->half_height) < EPSILON)
		normal = vector_scale(shape->dir, -1);
	else
	{
		axis_point = vector_add(shape->pos,
				vector_scale(shape->dir, hit_height));
		normal = vector_subtract(hit->hit_point, axis_point);
	}
	return (vector_normalize(normal));
}

t_vector	cone_normal(t_hit *hit)
{
	t_shape		*shape;
	double		hit_height;
	t_vector	normal;
	t_vector	axis_point;
	t_vector	to_surface;

	shape = hit->shape;
	hit_height = vector_dot(
			vector_subtract(hit->hit_point, shape->pos), shape->dir);
	if (hit_height > (shape->height - EPSILON))
		normal = shape->dir;
	else
	{
		axis_point = vector_add(shape->pos,
				vector_scale(shape->dir, hit_height));
		to_surface = vector_subtract(hit->hit_point, axis_point);
		normal = vector_subtract(
				vector_scale(to_surface, shape->cos_theta),
				vector_scale(shape->dir,
					shape->sin_theta * vector_length(to_surface)));
	}
	return (vector_normalize(normal));
}

void	fix_hit_normal(t_hit *hit)
{
	if (hit->shape->type == PLANE)
		hit->normal = hit->shape->dir;
	else if (hit->shape->type == CYLINDER)
		hit->normal = cylinder_normal(hit);
	else if (hit->shape->type == CONE)
		hit->normal = cone_normal(hit);
	else if (hit->shape->type == SPHERE)
		hit->normal = vector_normalize(
				vector_subtract(hit->hit_point, hit->shape->pos));
	if (vector_dot(hit->ray->direction, hit->normal) > 0)
	{
		hit->inshape = true;
		hit->normal = vector_scale(hit->normal, -1);
	}
	hit->normal_pre_perturb = hit->normal;
}
