/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:11:55 by aklein            #+#    #+#             */
/*   Updated: 2024/09/23 20:41:46 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

bool	check_shadow(t_hit *hit, t_light *light)
{
	t_ray		shadow_ray;
	t_hit		temp;
	double		light_distance;
	t_vector	direction;

	temp = new_hit();
	direction = vector_subtract(
			light->pos,
			hit->hit_point);
	light_distance = vector_length(direction);
	shadow_ray = create_ray(hit->hit_point, direction);
	temp.t = light_distance;
	if (intersect_bvh(rtx()->bvh, &shadow_ray, &temp)
		&& temp.t < light_distance)
		return (true);
	temp.t = light_distance;
	if (check_unbound(&shadow_ray, &temp)
		&& temp.t < light_distance)
		return (true);
	return (false);
}

double	get_specular(t_hit *hit, t_vector *light_dir)
{
	t_vector	reflection;
	t_vector	hit_view;
	double		reflection_angle;
	double		specular;
	double		intensity_scale;

	if (hit->shape->shine == 0)
		return (0.0);
	hit_view = vector_normalize(
			vector_subtract(rtx()->camera.pos, hit->hit_point));
	reflection_angle = vector_dot(*light_dir, hit->normal) * 2.0;
	reflection = vector_scale(hit->normal, reflection_angle);
	reflection = vector_normalize(vector_subtract(reflection, *light_dir));
	specular = fmax(vector_dot(reflection, hit_view), 0.0);
	specular = pow(specular, hit->shape->shine);
	intensity_scale = hit->shape->shine / (hit->shape->shine + SHINE_MOD);
	specular *= intensity_scale;
	return (specular);
}

double	get_diffuse(t_hit *hit, t_vector *light_dir)
{
	double	diffuse;

	diffuse = fmax(vector_dot(hit->normal, *light_dir), 0.0);
	return (diffuse);
}

void	light_one(t_lighting *lighting, t_light *light,
			t_hit *hit, double intensity_scale)
{
	t_vector	light_dir;
	double		diff_int;
	double		spec_int;
	t_color		diff_contrib;
	t_color		spec_contrib;

	light_dir = vector_normalize(vector_subtract(light->pos, hit->hit_point));
	if (vector_dot(hit->normal_pre_perturb, light_dir) < -EPSILON)
		return ;
	diff_int = get_diffuse(hit, &light_dir);
	spec_int = get_specular(hit, &light_dir);
	diff_contrib = color_scale(light->color,
			diff_int * intensity_scale);
	spec_contrib = color_scale(light->color,
			spec_int * intensity_scale);
	lighting->diffuse = color_add(lighting->diffuse, diff_contrib);
	lighting->specular = color_add(lighting->specular, spec_contrib);
}

t_lighting	calc_lighting(t_hit *hit)
{
	t_list		*lights;
	t_light		*light;
	t_lighting	lighting;

	lights = rtx()->lights;
	lighting = (t_lighting){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	while (lights)
	{
		light = (t_light *)lights->content;
		if (!check_shadow(hit, light))
			light_one(&lighting, light, hit, light->bright);
		lights = lights->next;
	}
	lighting.diffuse = color_clamp(lighting.diffuse);
	lighting.specular = color_clamp(lighting.specular);
	return (lighting);
}
