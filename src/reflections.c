#include <miniRT.h>

t_color	get_reflections(t_hit *hit, int depth)
{
	t_ray		reflection_ray;
	t_vector	reflect;
	t_color		reflection_color;

	reflect = vector_subtract(
		hit->ray->direction,
		vector_scale(hit->normal, 2 * vector_dot(hit->ray->direction, hit->normal)));
	reflection_ray = create_ray(hit->hit_point, reflect);
	reflection_color = trace_ray(&reflection_ray, depth);
	return (reflection_color);
}