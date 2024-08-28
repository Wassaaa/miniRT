/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:25 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:25:33 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	sphere_uv(t_hit *hit, double *u, double *v, int repeat)
{
	double		phi;
	double		theta;
	t_vector	local_point;
	t_shape		*shape;

	shape = hit->shape;
	local_point = hit->normal;
	local_point = (t_vector){
		vector_dot(local_point, shape->u_axis),
		vector_dot(local_point, shape->dir),
		vector_dot(local_point, shape->v_axis)};
	local_point = vector_normalize(local_point);
	phi = atan2(local_point.z, local_point.x);
	theta = acos(local_point.y);
	*u = (phi + M_PI) / (2 * M_PI);
	*v = theta / M_PI;
	uv_repeat_wrap(u, v, repeat);
}

/*
1. Convert hit point to local coordinates
2. Create a consistent local coordinate system
3. Calculate UV coordinates
*/
static void	plane_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	u_axis;
	t_vector	v_axis;
	t_vector	local_point;

	local_point = vector_subtract(hit->hit_point, hit->shape->pos);
	u_axis = hit->shape->u_axis;
	v_axis = hit->shape->v_axis;
	*u = vector_dot(u_axis, local_point) * SCALE_PLANE;
	*v = vector_dot(v_axis, local_point) * SCALE_PLANE;
	uv_repeat_wrap(u, v, repeat);
}

static void	cylindrical_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	local_point;
	t_vector	u_axis;
	t_vector	v_axis;
	double		height;
	double		theta;

	u_axis = hit->shape->u_axis;
	v_axis = hit->shape->v_axis;
	local_point = vector_subtract(hit->hit_point, hit->shape->pos);
	height = vector_dot(local_point, hit->shape->dir);
	height += (hit->shape->half_height);
	if (fabs(vector_dot(hit->normal, hit->shape->dir)) > 1 - EPSILON)
	{
		*u = (vector_dot(local_point, u_axis) / hit->shape->radius + 1) / 2;
		*v = (vector_dot(local_point, v_axis) / hit->shape->radius + 1) / 2;
	}
	else
	{
		theta = atan2(vector_dot(local_point, v_axis),
				vector_dot(local_point, u_axis));
		*u = (theta + M_PI) / (2 * M_PI);
		*v = height / hit->shape->height;
	}
	uv_repeat_wrap(u, v, repeat);
}

void	get_uv(t_hit *hit)
{
	double	u;
	double	v;
	t_shape	*shape;

	u = 0.0;
	v = 0.0;
	shape = hit->shape;
	if (shape->type == SPHERE)
		sphere_uv(hit, &u, &v, 1);
	else if (shape->type == PLANE)
		plane_uv(hit, &u, &v, 1);
	else if (shape->type == CYLINDER)
		cylindrical_uv(hit, &u, &v, 1);
	else if (shape->type == CONE)
		cylindrical_uv(hit, &u, &v, 1);
	hit->u = u;
	hit->v = v;
}
