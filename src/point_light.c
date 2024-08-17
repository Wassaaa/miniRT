#include <miniRT.h>

bool	check_shadow(t_hit *hit, t_light *light)
{
	t_ray		shadow_ray;
	t_hit		temp;
	double		light_distance;
	t_vector	origin;
	t_vector	direction;
	
	origin = vector_add(hit->hit_point, vector_scale(hit->normal, EPSILON));
	direction = vector_subtract(
		light->pos,
		origin);
	light_distance = vector_length(direction);
	direction = vector_scale(direction, 1.0 / light_distance);
	shadow_ray = create_ray(origin, direction);
	temp.distance = light_distance;
	if (rtx()->bvh && intersect_bvh(rtx()->bvh, &shadow_ray, &temp) && temp.distance < light_distance)
		return (true);
	temp.distance = light_distance;
	if (check_unbound(&shadow_ray, &temp) && temp.distance < light_distance)
		return (true);
	return (false);
}

double	get_specular(t_hit *hit, t_vector *light_dir)
{
	t_vector	reflection;
	t_vector	hit_view;
	double		reflection_angle;
	double		specular;

	hit_view = vector_normalize(vector_scale(hit->hit_point, -1));
	reflection_angle = vector_dot(*light_dir, hit->normal) * 2.0;
	reflection = vector_scale(hit->normal, reflection_angle);
	reflection = vector_subtract(reflection, *light_dir);
	specular = fmax(vector_dot(reflection, hit_view), 0.0);
	specular = pow(specular, hit->shape->shine);
	return (specular);
}

double	get_diffuse(t_hit *hit, t_vector *light_dir)
{
	double	diffuse;

	diffuse = fmax(
		vector_dot(hit->normal, *light_dir), 0.0);
	return (diffuse);
}

void	light_one(t_lighting *lighting, t_light *light, t_hit *hit)
{
	t_vector	light_dir;
	double		diff_int;
	double		spec_int;
	t_color		diff_contrib;
	t_color		spec_contrib;

	light_dir = vector_normalize(
		vector_subtract(light->pos, hit->hit_point));
	diff_int = get_diffuse(hit, &light_dir);
	spec_int = get_specular(hit, &light_dir);
	diff_contrib = color_scale(light->color, light->bright * diff_int);
	spec_contrib = color_scale(light->color, light->bright * spec_int);
	lighting->diffuse = color_add(lighting->diffuse, diff_contrib);
	lighting->specular = color_add(lighting->specular, spec_contrib);
}

t_lighting	calc_lighting(t_hit *hit)
{
	t_list		*lights;
	t_light		*light;
	t_lighting	lighting;
	double		total_intensity;

	lights = rtx()->lights;
	lighting = (t_lighting){{0, 0, 0},{0, 0, 0},{0, 0, 0}};
	total_intensity = 0.0;
	while (lights)
	{
		light = (t_light *)lights->content;
		if (!check_shadow(hit, light))
		{
			light_one(&lighting, light, hit);
			total_intensity += light->bright;
		}
		lights = lights->next;
	}
	if (total_intensity > 1.0)
	{
		lighting.diffuse = color_scale(lighting.diffuse, 1.0 / total_intensity);
		// lighting.specular = color_scale(lighting.specular, 1.0 / total_intensity);
	}
	return (lighting);
}
