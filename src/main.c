#include <miniRT.h>

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}

t_sphere	make_sphere(t_vector pos, double diameter, t_rgba color)
{
	t_sphere	sphere;

	sphere.pos = pos;
	sphere.diameter = diameter;
	sphere.radius = sphere.diameter / 2;
	sphere.color = color;

	return (sphere);
}

t_plane	make_plane(t_vector pos, t_vector dir, t_rgba color)
{
	t_plane	plane;

	plane.pos = pos;
	plane.dir = dir;
	plane.color = color;

	return (plane);
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	get_rgba(t_rgba color, double intensity)
{
	t_rgba	result;

	result.r = clamp((int)(color.r * intensity), 0, 255);
	result.g = clamp((int)(color.g * intensity), 0, 255);
	result.b = clamp((int)(color.b * intensity), 0, 255);
	result.a = clamp(color.a, 0, 255);
	return (result.r << 24 | result.g << 16 | result.b << 8 | result.a);
}

int	get_pixel_color(t_ray ray, t_sphere sphere, double t)
{
	t_vector	hit_point;
	t_vector	normal;
	double		intensity;
	t_vector	light = vector_normalize(TEST_LIGHT);
	double		ambient;
	
	hit_point = vector_add(ray.origin, vector_multiply(ray.direction, t));
	normal = vector_normalize(vector_subtract(hit_point, sphere.pos));
	ambient = TEST_AMBIENT;
	intensity = fmax(vector_dot(normal, light), 0.0) + ambient;
	return (get_rgba(sphere.color, intensity));
}

int get_color(t_ray ray)
{
	double		t;
	t_sphere	sphere = make_sphere(TEST_SPHERE);

	if (sphere_intersect(ray, sphere, &t))
		return (get_pixel_color(ray, sphere, t));
	return (TEST_BG);
}

t_ray	generate_ray(int x, int y)
{
	t_ray		ray;
	t_vector	vector;
	double		fov;

	ft_memset(&ray, 0, sizeof(t_ray));
	fov = tan((TEST_FOV / 2) * (M_PI / 180.0));
	vector.x = (2 * ((x + 0.5) / WIDTH) - 1) * fov * WIDTH / HEIGHT;
	vector.y = (1 - 2 * ((y + 0.5) / HEIGHT)) * fov;
	vector.z = 1;
	ray.direction = vector_normalize(vector);
	return (ray);
}

void	render_scene(void)
{
	t_ray	ray;
	int		color;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			ray = generate_ray(x, y);
			color = get_color(ray);
			mlx_put_pixel(rtx()->img, x, y, color);
		}
	}
}

void	start_mlx(void)
{
	rtx()->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 0);
	rtx()->img = mlx_new_image(rtx()->mlx, WIDTH, HEIGHT);
	if (!rtx()->img)
		exit(1);
	rtx()->width = WIDTH;
	rtx()->height = HEIGHT;
	mlx_image_to_window(rtx()->mlx, rtx()->img, 0, 0);
}

int	main(void)
{
	start_mlx();
	render_scene();
	mlx_loop(rtx()->mlx);
	mlx_terminate(rtx()->mlx);
	return (0);
}
