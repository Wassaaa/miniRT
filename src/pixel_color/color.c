/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:20 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:21:48 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	fix_hit(t_hit *hit)
{
	hit->hit_point = vector_add(
			hit->ray->origin,
			vector_scale(hit->ray->direction, hit->t));
	fix_hit_normal(hit);
	get_uv(hit);
}

void	sample_bumps(t_hit *hit, double *dh_du, double *dh_dv)
{
	double	h;
	double	u_step;
	double	v_step;

	h = uv_get_color(hit->shape->bump, hit->u, hit->v).r / 255.0;
	u_step = 1.0 / hit->shape->bump->width;
	v_step = 1.0 / hit->shape->bump->height;
	*dh_du = uv_get_color(hit->shape->bump, hit->u + u_step, hit->v).r / 255.0;
	*dh_dv = uv_get_color(hit->shape->bump, hit->u, hit->v + v_step).r / 255.0;
	*dh_du = (*dh_du - h) / u_step;
	*dh_dv = (*dh_dv - h) / v_step;
}

void	perturb_normal(t_hit *hit)
{
	double		dh_du;
	double		dh_dv;
	t_shape		*shape;
	t_vector	tangent_normal;

	shape = hit->shape;
	if (shape->bump)
	{
		sample_bumps(hit, &dh_du, &dh_dv);
		tangent_normal = vector_add(
				vector_scale(shape->u_axis, -dh_du),
				vector_scale(shape->v_axis, -dh_dv));
		tangent_normal = vector_scale(tangent_normal, BUMP_STR);
		hit->normal = vector_add(
				hit->normal,
				tangent_normal);
		hit->normal = vector_normalize(hit->normal);
	}
}

t_color	ambient_factor(t_hit *hit)
{
	double		factor;
	t_color		ambient;

	factor = (vector_dot(hit->normal, hit->normal_pre_perturb) + 1.0) * 0.5;
	factor = fmax(factor, 0.1);
	ambient = color_scale(rtx()->ambient, factor);
	return (ambient);
}

t_color	get_pixel_color(t_ray *ray, t_hit *hit, int depth)
{
	t_lighting	lighting;
	t_color		material_color;
	t_color		final_color;
	t_color		diffuse_and_ambient;
	t_color		reflection;

	if (hit->shape->type == WIREFRAME)
		return (hit->shape->color);
	hit->ray = ray;
	fix_hit(hit);
	perturb_normal(hit);
	lighting = calc_lighting(hit);
	lighting.ambient = ambient_factor(hit);
	material_color = add_material(hit);
	diffuse_and_ambient = color_add(lighting.diffuse, lighting.ambient);
	final_color = color_multiply(diffuse_and_ambient, material_color);
	final_color = color_add(final_color, lighting.specular);
	if (!hit->inshape && hit->shape->reflectivity > 0.0 && depth > 0)
	{
		reflection = get_reflections(hit, depth - 1);
		final_color = color_blend(
				final_color,
				reflection, hit->shape->reflectivity);
	}
	return (color_scale(final_color, 1.0 / GAMMA));
}
