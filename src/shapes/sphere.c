/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:28 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:26:46 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Sphere equation: (P - C) · (P - C) = r^2
	P is any point on the sphere's surface
	C is the center of the sphere
	r is the radius of the sphere
	(P - C) represents a vector from the center to any point on the surface
	(P - C) · (P - C) is the dot product of this vector with itself, which
	gives us the square of its length
The square of the distance between any point on the sphere (P) and the
center of the sphere (C)
is equal to the square of the radius (r^2)."

Ray equation: P(t) = O + tD
	P(t) is any point along the ray
	O is the origin point of the ray
	D is the direction vector of the ray
	t is a scalar parameter that determines how far along the ray we are
Any point on the ray can be found by
starting at the origin O and moving some distance t in direction D.

combine the 2 equations and find where the ray intersects with the sphere
ax² + bx + c = 0
x = (-b ± √(b² - 4ac)) / (2a)

(O - C) · (O - C) + 2t((O - C) · D) + t²(D · D) = r²

(D · D)t² + 2((O - C) · D)t + ((O - C) · (O - C) - r²) = 0
|  a  |     |     b      |    |          c           |
*/
t_quad_coeffs	quadratic_coeffs_sphere(t_ray *ray, t_shape *shape)
{
	t_quad_coeffs	coeffs;
	t_vector		oc;

	oc = vector_subtract(ray->origin, shape->pos);
	coeffs.a = vector_dot(ray->direction, ray->direction);
	coeffs.b = 2.0 * vector_dot(oc, ray->direction);
	coeffs.c = vector_dot(oc, oc) - (shape->radius * shape->radius);
	return (coeffs);
}

bool	intersect_sphere(t_ray *ray, t_shape *sphere, double *t)
{
	t_quad_coeffs	coeffs;
	double			discriminant;
	double			t_body[2];

	coeffs = quadratic_coeffs_sphere(ray, sphere);
	discriminant = (coeffs.b * coeffs.b) - (4 * coeffs.a * coeffs.c);
	if (discriminant < 0)
		return (false);
	get_valid_t(t_body, &coeffs, &discriminant);
	*t = t_body[0];
	return (*t > 0);
}
