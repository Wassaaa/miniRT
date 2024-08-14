#include <miniRT.h>

void	fix_hit(t_hit *hit)
{
	hit->hit_point = vector_add(
		hit->ray->origin,
		vector_scale(hit->ray->direction, hit->distance));
	fix_hit_normal(hit);
	get_uv(hit);
}

t_color	get_pixel_color(t_ray *ray, t_hit *hit, int depth)
{
	t_lighting	lighting;
	t_color		material_color;
	t_color		final_color;
	t_color		diffuse_and_ambient;
	t_color		reflection;
	

	hit->ray = ray;
	fix_hit(hit);
	if (hit->shape->type == WIREFRAME)
		final_color = hit->shape->color;
	else
	{
		lighting = calc_lighting(hit);
		material_color = add_material(hit);
		diffuse_and_ambient = color_add(lighting.diffuse, lighting.ambient);
		final_color = color_multiply(diffuse_and_ambient, material_color);
		final_color = color_add(final_color, lighting.specular);
		if (hit->shape->reflectivity > 0.0 && depth > 0)
		{
			reflection = get_reflections(hit, depth - 1);
			final_color = color_blend(final_color, reflection, hit->shape->reflectivity);
		}
	}
	return (final_color);
}
