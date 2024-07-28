#include <miniRT.h>

int	get_pixel_color(t_ray *ray, t_hit *hit)
{
	t_color	final_color;
	
	hit->hit_point = vector_add(
		ray->origin,
		vector_scale(ray->direction, hit->distance));
	fix_hit_normal(hit);
	if (hit->shape->type == WIREFRAME
		|| hit->shape->type == LINE
		)
		final_color = hit->shape->color;
	else
		final_color = get_diffuse(hit);
	return (color_to_int(final_color));
}
