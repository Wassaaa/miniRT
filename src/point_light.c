#include <miniRT.h>

bool	check_shadow(t_hit *hit, t_light *light)
{
	t_ray	shadow_ray;
	t_hit	temp;
	double	light_distance;
	
	shadow_ray.origin = vector_add(hit->hit_point, vector_scale(hit->normal, 0.001));
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


double	diffuse_one(t_light *light, t_hit *hit)
{
	t_vector	light_dir;
	double		intensity;

	light_dir = vector_normalize(
		vector_subtract(light->pos, hit->hit_point));
	intensity = vector_dot(hit->normal, light_dir);
	intensity = fmax(intensity, 0.0);
	intensity *= light->bright;
	return (intensity);
}

t_color	get_diffuse(t_hit *hit)
{
	t_list	*lights;
	t_light	*current_light;
	t_color	total_light;
	t_color	light_contribution;
	double	intensity;

	total_light = (t_color){0, 0, 0};
	lights = rtx()->scene->lights;
	while (lights)
	{
		current_light = (t_light *)lights->content;
		if (!check_shadow(hit, current_light))
		{
			intensity = diffuse_one(current_light, hit);
			light_contribution = color_scale(current_light->color, intensity);
			light_contribution = color_multiply(light_contribution, hit->shape->color);
			total_light = color_add(total_light, light_contribution);
		}
		lights = lights->next;
	}
	light_contribution = color_multiply(rtx()->scene->ambient, hit->shape->color);
	total_light = color_add(total_light, light_contribution);
	return (color_clamp(total_light));
}
