/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:32 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 19:02:19 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

bool	check_unbound(t_ray *ray, t_hit *hit)
{
	t_list	*unbound;
	t_shape	*shape;
	double	t;

	unbound = rtx()->unbound;
	while (unbound)
	{
		shape = (t_shape *)unbound->content;
		if (shape->type == PLANE)
		{
			if (intersect_plane(ray, shape, &t) && t < hit->t)
			{
				hit->t = t;
				hit->shape = shape;
				hit->hit = true;
			}
		}
		unbound = unbound->next;
	}
	return (hit->hit);
}

void	ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	get_valid_t(double t_body[2], t_quad_coeffs *coeffs, double *disc)
{
	t_body[0] = (-coeffs->b - sqrt(*disc)) / (2.0 * coeffs->a);
	t_body[1] = (-coeffs->b + sqrt(*disc)) / (2.0 * coeffs->a);
	if (t_body[0] < 0)
		t_body[0] = INFINITY;
	if (t_body[1] < 0)
		t_body[1] = INFINITY;
	if (t_body[1] < t_body[0])
		ft_swap(&t_body[0], &t_body[1]);
}

bool	intersect(t_shape *shape, t_ray *ray, double *t)
{
	bool	hit;

	hit = false;
	if (shape->type == SPHERE)
		hit = intersect_sphere(ray, shape, t);
	else if (shape->type == CYLINDER)
		hit = intersect_cylinder(ray, shape, t);
	else if (shape->type == CONE)
		hit = intersect_cone(ray, shape, t);
	else if (shape->type == WIREFRAME)
		hit = intersect_aabb_line(ray, shape, t);
	if (*t < 0)
		return (false);
	return (hit && *t > 0);
}
