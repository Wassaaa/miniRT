#include <miniRT.h>

t_light	create_point_light(t_vector pos, double bright)
{
	t_light	light;

	light.pos = pos;
	light.bright = bright;

	return (light);
}

bool	check_shadow(t_intersection *t, t_light *light)
{
	t_ray			shadow_ray;
	t_intersection	temp;
	double			light_distance;
	
	shadow_ray.origin = vector_add(t->hit_point, vector_scale(t->normal, 0.001));
	shadow_ray.direction = vector_subtract(
			light->pos,
			shadow_ray.origin);
	light_distance = vector_length(shadow_ray.direction);
	shadow_ray.direction = vector_scale(shadow_ray.direction, 1.0 / light_distance);
	shadow_ray.inv_dir = (t_vector){
		1.0 / shadow_ray.direction.x,
		1.0 / shadow_ray.direction.y,
		1.0 / shadow_ray.direction.z
	};
	temp.distance = light_distance;
	if (rtx()->bvh && intersect_bvh(rtx()->bvh, shadow_ray, &temp) && temp.distance < light_distance)
		return (true);
	temp.distance = light_distance;
	if (check_unbound(&shadow_ray, &temp) && temp.distance < light_distance)
		return (true);
	return (false);
}
t_rgba	color_scale(t_rgba color, double intensity)
{
	t_rgba	result;

	result.r = clamp((int)(color.r * intensity), 0, 255);
	result.g = clamp((int)(color.g * intensity), 0, 255);
	result.b = clamp((int)(color.b * intensity), 0, 255);
	result.a = clamp(color.a, 0, 255);
	return (result);
}

t_rgba	diffuse_one(t_light *light, t_intersection *t)
{
	t_rgba		diffuse;
	t_vector	light_dir;
	double		intensity;

	light_dir = vector_normalize(
		vector_subtract(light->pos, t->hit_point));
	intensity = vector_dot(t->normal, light_dir);
	intensity = fmax(intensity, 0.0);
	intensity *= light->bright;
	diffuse = color_scale(light->color, intensity);
	return (diffuse);
}

get_diffuse(t_intersection *t)
{
	t_scene	*scene;
	t_list	*lights;
	t_light	*current_light;
	t_rgba	total_diffuse;
	t_rgba	light_diffuse;

	total_diffuse = (t_rgba){0, 0, 0, 0};
	scene = rtx()->scene;
	lights = scene->lights;
	while (lights)
	{
		current_light = (t_light *)lights->content;
		diffuse_one(current_light, t);
		if (!check_shadow)
		total_diffuse = 
	}
}

double light_intensity(t_intersection *t)
{
	double		intensity;
	double		diffuse;
	t_vector	light_dir;

	intensity = rtx()->scene->amb.amb_light;
	light_dir = vector_subtract(
		rtx()->scene->light.pos,
		t->hit_point);
	light_dir = vector_normalize(light_dir);
	if (!check_shadow(t))
	{
		diffuse = fmax(vector_dot(t->normal, light_dir), 0.0) * rtx()->scene->light.bright;
		intensity += diffuse;
	}

	return (intensity);
}