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

t_color	light_one(t_light *light, t_hit *hit)
{
	t_vector	light_dir;
	double		intensity;
	t_color		contribution;

	contribution = light->color;
	light_dir = vector_normalize(
		vector_subtract(light->pos, hit->hit_point));
	intensity = vector_dot(hit->normal, light_dir);
	intensity = fmax(intensity, 0.0);

	contribution = color_scale(contribution, light->bright * intensity);
	return (contribution);
}

t_lighting	calc_lighting(t_hit *hit)
{
	t_list		*lights;
	t_light		*light;
	t_lighting	lighting;
	t_color		contribution;
	t_color		total;

	lights = rtx()->scene->lights;
	lighting = (t_lighting){{0, 0, 0},{0, 0, 0},{0, 0, 0}};
	contribution = color_create(0, 0, 0);
	total = color_create(0, 0, 0);
	lighting.ambient = rtx()->scene->ambient;
	while (lights)
	{
		light = (t_light *)lights->content;
		if (!check_shadow(hit, light))
		{
			contribution = light_one(light, hit);
			total = color_add(total, contribution);
		}
		lights = lights->next;
	}
	lighting.direct = total;
	return (lighting);
}
