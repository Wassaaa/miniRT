/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:01 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:33:57 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_quad_coeffs	quadratic_coeffs_cone(t_ray *ray, t_shape *cone)
{
	t_quad_coeffs	coeffs;
	t_vector		oc;

	oc = vector_subtract(ray->origin, cone->pos);
	coeffs.a = vector_dot(ray->direction, ray->direction)
		- cone->k
		* pow(vector_dot(ray->direction, cone->dir), 2);
	coeffs.b = 2 * (vector_dot(ray->direction, oc)
			- cone->k
			* vector_dot(ray->direction, cone->dir)
			* vector_dot(oc, cone->dir));
	coeffs.c = vector_dot(oc, oc)
		- cone->k
		* pow(vector_dot(oc, cone->dir), 2);
	return (coeffs);
}

double	intersect_cone_base(t_ray *ray, t_shape *cone)
{
	t_vector	base_center;
	double		t;
	t_vector	p;

	base_center = vector_subtract(
			cone->pos,
			vector_scale(cone->dir, -cone->height));
	t = vector_dot(
			vector_subtract(base_center, ray->origin),
			cone->dir);
	t = t / vector_dot(ray->direction, cone->dir);
	if (t > 0)
	{
		p = vector_subtract(
				vector_add(ray->origin, vector_scale(ray->direction, t)),
				base_center);
		if (vector_dot(p, p) <= cone->radius * cone->radius)
			return (t);
	}
	return (INFINITY);
}

void	check_height(double t_body[2], t_ray *ray, t_shape *cone)
{
	t_vector	intersection;
	int			i;
	double		y;

	if (t_body[0] == INFINITY)
		return ;
	i = 0;
	while (i < 2)
	{
		intersection = vector_add(
				ray->origin,
				vector_scale(ray->direction, t_body[i]));
		y = vector_dot(
				vector_subtract(intersection, cone->pos),
				cone->dir);
		if (y < 0 || y > cone->height)
			t_body[i] = INFINITY;
		i++;
	}
	if (t_body[0] > t_body[1])
		ft_swap(&t_body[0], &t_body[1]);
}

int	intersect_cone(t_ray *ray, t_shape *cone, double *t)
{
	t_quad_coeffs	coeffs;
	double			discriminant;
	double			t_body[2];

	coeffs = quadratic_coeffs_cone(ray, cone);
	discriminant = (coeffs.b * coeffs.b) - (4 * coeffs.a * coeffs.c);
	if (discriminant < 0)
		return (0);
	get_valid_t(t_body, &coeffs, &discriminant);
	check_height(t_body, ray, cone);
	*t = fmin(t_body[0], intersect_cone_base(ray, cone));
	return (*t != INFINITY);
}
