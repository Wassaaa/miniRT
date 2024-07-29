#include <miniRT.h>


void sphere_uv(t_vector point, double *u, double *v)
{
	double phi = atan2(point.z, point.x);
	double theta = asin(point.y);
	
	*u = 1 - (phi + M_PI) / (2 * M_PI);
	*v = (theta + M_PI / 2) / M_PI;
}

int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	int32_t	color;

	color = r << 24 | g << 16 | b << 8 | a;
	return (color);
}

static t_color	color_from_memory(mlx_texture_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*start;
	t_color	color;

	start = img->pixels + (y * img->width + x) * img->bytes_per_pixel;
	color.r = *(start);
	color.g = *(start + 1);
	color.b = *(start + 2);
	return (color);
}

t_color	add_material(t_hit *hit)
{
	double	u;
	double	v;
	t_shape	*sphere;
	t_color	color;

	sphere = hit->shape;
	sphere_uv(hit->hit_point, &u, &v);
	color = color_from_memory(sphere->texture, u, v);
	return (color);
}

t_color	get_pixel_color(t_ray *ray, t_hit *hit)
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
	{
		final_color = get_diffuse(hit);
		final_color = add_material(hit);
	}
	return (final_color);
}
