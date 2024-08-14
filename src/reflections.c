#include <miniRT.h>

t_color	get_reflections(t_hit *hit, int depth)
{
	t_ray		reflection_ray;
	t_vector	reflect;
	t_color		reflection_color;

	reflect = vector_subtract(
		hit->ray->direction,
		vector_scale(hit->normal, 2 * vector_dot(hit->ray->direction, hit->normal)));
	reflection_ray.origin = vector_add(
		hit->hit_point,
		vector_scale(hit->normal, EPSILON));
	reflection_ray.direction = vector_normalize(reflect);
	reflection_ray.inv_dir = (t_vector){
		1.0 / reflection_ray.direction.x,
		1.0 / reflection_ray.direction.y,
		1.0 / reflection_ray.direction.z
	};
	reflection_color = trace_ray(&reflection_ray, depth);
	return (reflection_color);
}