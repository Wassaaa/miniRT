#include <miniRT.h>

int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	int32_t	color;

	color = r << 24 | g << 16 | b << 8 | a;
	return (color);
}

/*
returns a normalized t_color from memory location at x y of image img
*/
static t_color	color_from_image(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*start;
	t_color	color;

	start = img->pixels + (y * img->width + x) * 4;
	color.r = (double)*(start) / 255.0;
	color.g = (double)*(start + 1) / 255.0;
	color.b = (double)*(start + 2) / 255.0;
	return (color);
}

int wrap_coordinate(int value, int max)
{
	value = value % max;
	if (value < 0)
		value += max;
	return (value);
}

t_color	get_texture_uv(mlx_image_t *image, double u, double v)
{
	int		x;
	int		y;
	int		width;
	int		height;

	width = image->width - 1;
	height = image->height - 1;
	x = (int)(width * u);
	y = (int)(height * v);
	x = wrap_coordinate(x, width);
	y = wrap_coordinate(y, height);
	return (color_from_image(image, x, y));
}

t_color	add_material(t_hit *hit)
{
	double	u;
	double	v;
	t_shape	*shape;
	t_color	color;

	u = 0.0;
	v = 0.0;
	shape = hit->shape;
	if (shape->type == SPHERE)
		sphere_uv(hit->normal, &u, &v, 1);
	else if (shape->type == PLANE)
		plane_uv(hit, &u, &v, 1);
	else if (shape->type == CYLINDER)
		cylindrical_uv(hit, &u, &v, 1);
	else if (shape->type == CONE)
		cone_uv(hit, &u, &v, 1);
	if (shape->image)
		color = get_texture_uv(shape->image, u, v);
	else
		color = shape->color;
	return (color);
}

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

t_color debug_normal_color(t_vector normal)
{
	return (t_color){
		(normal.x + 1) * 0.5,
		(normal.y + 1) * 0.5,
		(normal.z + 1) * 0.5
	};
}

t_color	get_pixel_color(t_ray *ray, t_hit *hit, int depth)
{
	t_lighting	lighting;
	t_color		material_color;
	t_color		final_color;
	t_color		diffuse_and_ambient;
	t_color		reflection;
	
	hit->hit_point = vector_add(
		ray->origin,
		vector_scale(ray->direction, hit->distance));
	hit->ray = ray;
	fix_hit_normal(hit);
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
