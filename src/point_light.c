#include <miniRT.h>

t_light	create_point_light(t_vector pos, double bright)
{
	t_light	light;

	light.pos = pos;
	light.bright = bright;

	return (light);
}

bool	check_shadow(t_intersection *t)
{
	bool	shadow;
	t_ray	shadow_ray;
	
	shadow_ray.origin = t->hit_point;
	shadow_ray.direction = vector_normalize(
		vector_subtract(
			rtx()->scene->light.pos,
			shadow_ray.origin));
	shadow_ray.inv_dir = (t_vector){
		1.0 / shadow_ray.direction.x,
		1.0 / shadow_ray.direction.y,
		1.0 / shadow_ray.direction.z
	};
	shadow = intersect_bvh(rtx()->bvh, shadow_ray, t);
	return (shadow);
}

double light_intensity(t_intersection *t)
{
	double		intentsity;
	double		brightness;
	t_vector	light;

	brightness = rtx()->scene->amb.amb_light;
	light = vector_subtract(
		rtx()->scene->light.pos,
		t->hit_point);
	light = vector_normalize(light);
	if (!check_shadow(t))
		brightness = vector_dot(t->normal, light) * rtx()->scene->light.bright;
	intentsity = fmax(brightness, rtx()->scene->amb.amb_light);

	return (intentsity);
}