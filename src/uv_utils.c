/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:18 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:18:19 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	uv_repeat_wrap(double *u, double *v, int repeat)
{
	*u *= repeat;
	*v *= repeat;
	*u = fmod(*u, 1.0);
	*v = fmod(*v, 1.0);
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
}

void	create_local_system(t_shape *shape)
{
	t_vector	u_axis;
	t_vector	v_axis;
	t_vector	normal;

	normal = shape->dir;
	u_axis = vector_cross(normal, WORLD_UP);
	if (vector_length(u_axis) < EPSILON)
		u_axis = vector_cross(normal, WORLD_RIGHT);
	u_axis = vector_normalize(u_axis);
	v_axis = vector_normalize(vector_cross(normal, u_axis));
	shape->u_axis = u_axis;
	shape->v_axis = v_axis;
}