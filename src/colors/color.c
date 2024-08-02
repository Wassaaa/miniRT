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

t_color	get_texture_uv(mlx_image_t *image, double *u, double *v)
{
	int		x;
	int		y;
	int		width;
	int		height;

	width = image->width - 1;
	height = image->height - 1;
	x = clampi(width * *u, 0, width);
	y = clampi(height * *v, 0, height);
	return (color_from_image(image, x, y));
}

t_color	create_checkboard(double *u, double *v)
{
	double	u_scaled;
	double	v_scaled;
	int		u_check;
	int		v_check;

	v_scaled = *v * SCALE;
	u_scaled = *u * SCALE;
	u_check = (int)floor(u_scaled) % 2;
	v_check = (int)floor(v_scaled) % 2;
	if ((u_check + v_check) % 2 == 0)
		return ((t_color){1.0, 1.0, 1.0});
	else
		return ((t_color){0.0, 0.0, 0.0});
}

t_color	create_checkboard_plane(t_vector hit)
{
	int	x;
	int	y;
	int	z;

	x = (int)floor(0.5 * hit.x);
	y = (int)floor(0.5 * hit.y);
	z = (int)floor(0.5 * hit.z);
	if ((x + y + z) % 2)
		return ((t_color){1.0, 1.0, 1.0});
	else
		return ((t_color){0.0, 0.0, 0.0});
}

t_color	add_material(t_hit *hit)
{
	double	u;
	double	v;
	t_shape	*shape;
	t_color	color;
	
	shape = hit->shape;
	if (shape->type == SPHERE)
		sphere_uv(hit->normal, &u, &v);
	else if (shape->type == PLANE)
		plane_uv(hit->normal, hit->hit_point, &u, &v);
	// else if (shape->type == CYLINDER)
	// 	cylinder_uv(hit->normal, &u, &v);
	// else if (shape->type == CONE)
	// 	cone_uv(hit->normal, &u, &v);
	if (shape->image)
		color = get_texture_uv(shape->image, &u, &v);
	else if (shape->checkerboard)
	{
		if (shape->type == SPHERE)
			color = create_checkboard(&u, &v);
		else if (shape->type == PLANE)
			color = create_checkboard_plane(hit->hit_point);
		else
			color = (t_color){0.0, 0.0, 0.0}; //need to fix
	}
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
	if (rtx()->debug_normals)
		return (debug_normal_color(hit->normal));
	if (hit->shape->type == WIREFRAME
		|| hit->shape->type == LINE
		)
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
