#include <miniRT.h>
t_color trace_ray(t_ray *ray, int depth)
{
	t_hit	hit;

	hit = (t_hit){INFINITY, NULL, false, VV, VV, NULL};
	if (rtx()->wireframe_bvh && rtx()->wireframe)
		hit.hit |= intersect_bvh(rtx()->wireframe_bvh, ray, &hit);
	if (rtx()->bvh)
		hit.hit |= intersect_bvh(rtx()->bvh, ray, &hit);
	hit.hit |= check_unbound(ray, &hit);
	if (!hit.hit)
		return (color_from_hex(TEST_BG));
	return (get_pixel_color(ray, &hit, depth));
}

t_vector	add_panning(t_vector *vector)
{
	t_vector	direction;
	t_vector	right;
	t_vector	up;

	right = rtx()->scene->camera.right;
	up = rtx()->scene->camera.up;
	direction = vector_add(
		vector_scale(right, vector->x),
		vector_scale(up, vector->y));
	direction = vector_add(
		direction,
		vector_scale(rtx()->scene->camera.dir, vector->z));
	return (direction);
}

t_ray	create_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vector_normalize(direction);
	ray.inv_dir = (t_vector){
		1.0 / ray.direction.x,
		1.0 / ray.direction.y,
		1.0 / ray.direction.z
	};
	return (ray);
}

t_ray	generate_ray(int x, int y)
{
	t_ray		ray;
	t_vector	vector;
	double		fov;
	t_scene		*scene;

	scene = rtx()->scene;
	ray.origin = rtx()->scene->camera.pos;
	fov = scene->camera.fov;
	vector.x = (2 * ((x + 0.5) / WIDTH) - 1) * fov * WIDTH / HEIGHT;
	vector.y = (1 - 2 * ((y + 0.5) / HEIGHT)) * fov;
	vector.z = 1;
	ray = create_ray(rtx()->scene->camera.pos, add_panning(&vector));
	return (ray);
}

void	render_scene(void)
{
	t_ray	ray;
	t_color	color;
	int		x;
	int		y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			ray = generate_ray(x, y);
			color = trace_ray(&ray, REFLECT_DEPTH);
			mlx_put_pixel(rtx()->img, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
}
