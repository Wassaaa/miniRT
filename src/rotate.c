/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:03 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:29:31 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Rodrigues' rotation formula
v_rotated = v * cos(θ) + (k × v) * sin(θ) + k * (k · v) * (1 - cos(θ))
*/
t_vector	vector_rotate(t_vector v, t_vector axis, double angle)
{
	t_vector	result;
	double		c;
	double		s;
	double		t;

	c = cos(angle);
	s = sin(angle);
	t = 1.0f - c;
	axis = vector_normalize(axis);
	result.x = v.x * (t * axis.x * axis.x + c)
		+ v.y * (t * axis.x * axis.y - s * axis.z)
		+ v.z * (t * axis.x * axis.z + s * axis.y);
	result.y = v.x * (t * axis.x * axis.y + s * axis.z)
		+ v.y * (t * axis.y * axis.y + c)
		+ v.z * (t * axis.y * axis.z - s * axis.x);
	result.z = v.x * (t * axis.x * axis.z - s * axis.y)
		+ v.y * (t * axis.y * axis.z + s * axis.x)
		+ v.z * (t * axis.z * axis.z + c);
	return (vector_normalize(result));
}

void	rotate_shape(t_shape *shape, t_vector axis, double angle)
{
	shape->dir = vector_rotate(shape->dir, axis, angle);
	shape->u_axis = vector_rotate(shape->u_axis, axis, angle);
	shape->v_axis = vector_rotate(shape->v_axis, axis, angle);
	if (shape->type != PLANE)
		shape->box = shape->boxfunc(shape);
}

bool	rotate_objects(t_direction dir)
{
	t_list		*shapes;
	t_shape		*shape;
	t_vector	axis;
	double		angle;

	if (rtx()->target > LIM_ROTATE)
		return (false);
	if (rtx()->target == PLANE)
		shapes = rtx()->unbound;
	else
		shapes = rtx()->shapes;
	axis = rtx()->camera.dir;
	angle = ROTATION_ANGLE * M_PI / 180;
	if (dir == FORWARD)
		angle = -angle;
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (shape->type == rtx()->target)
			rotate_shape(shape, axis, angle);
		shapes = shapes->next;
	}
	if (rtx()->target < LIM_BVH)
		rebuild_bvh();
	return (true);
}
