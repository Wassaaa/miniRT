/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:06 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:33:48 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_quad_coeffs	quadratic_coeffs_cylinder(t_ray *ray, t_shape *shape)
{
	t_quad_coeffs	coeffs;
	t_vector		oc;

	oc = vector_subtract(ray->origin, shape->pos);
	coeffs.a = vector_dot(ray->direction, ray->direction)
		- pow(vector_dot(ray->direction, shape->dir), 2);
	coeffs.b = 2 * (vector_dot(ray->direction, oc)
			- vector_dot(ray->direction, shape->dir)
			* vector_dot(oc, shape->dir));
	coeffs.c = vector_dot(oc, oc) - pow(vector_dot(oc, shape->dir), 2)
		- shape->radius * shape->radius;
	return (coeffs);
}

double	intersect_cylinder_caps(t_ray *ray, t_shape *cylinder)
{
	t_vector	v_caps[2];
	double		t_caps[2];
	t_vector	v;
	double		r_squared;
	int			i;

	i = -1;
	while (++i < 2)
	{
		v_caps[i] = vector_add(cylinder->pos, vector_scale(cylinder->dir,
					(i * 2 - 1) * cylinder->half_height));
		t_caps[i] = vector_dot(vector_subtract(v_caps[i], ray->origin),
				cylinder->dir) / vector_dot(ray->direction, cylinder->dir);
		if (t_caps[i] > 0)
		{
			v = vector_subtract(vector_add(ray->origin,
						vector_scale(ray->direction, t_caps[i])), v_caps[i]);
			r_squared = vector_dot(v, v) - pow(vector_dot(v, cylinder->dir), 2);
			if (r_squared > cylinder->radius * cylinder->radius)
				t_caps[i] = INFINITY;
		}
		else
			t_caps[i] = INFINITY;
	}
	return (fmin(t_caps[0], t_caps[1]));
}

int	intersect_cylinder(t_ray *ray, t_shape *cylinder, double *t)
{
	t_quad_coeffs	coeffs;
	double			discriminant;
	t_vector		intersection;
	double			t_body[2];
	double			y;

	coeffs = quadratic_coeffs_cylinder(ray, cylinder);
	discriminant = (coeffs.b * coeffs.b) - (4 * coeffs.a * coeffs.c);
	if (discriminant < 0)
		return (0);
	get_valid_t(t_body, &coeffs, &discriminant);
	if (t_body[0] > 0)
	{
		intersection = vector_add(ray->origin,
				vector_scale(ray->direction, t_body[0]));
		y = vector_dot(vector_subtract(intersection, cylinder->pos),
				cylinder->dir);
		if (fabs(y) > cylinder->half_height)
			t_body[0] = INFINITY;
	}
	else
		t_body[0] = INFINITY;
	*t = fmin(t_body[0], intersect_cylinder_caps(ray, cylinder));
	return (*t != INFINITY);
}
