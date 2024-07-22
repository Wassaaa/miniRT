#include <miniRT.h>

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}

t_shape	*make_sphere(t_vector pos, double diameter, t_rgba color)
{
	t_shape	*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHARE;
	sphere->pos = pos;
	sphere->diameter = diameter;
	sphere->radius = sphere->diameter / 2;
	sphere->color = color;

	return (sphere);
}

t_shape	*make_plane(t_vector pos, t_vector dir, t_rgba color)
{
	t_shape	*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	plane->pos = pos;
	plane->dir = dir;
	plane->color = color;

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

int	get_pixel_color(t_ray ray, t_shape sphere)
{
	t_vector	hit_point;
	t_vector	normal;
	double		intensity;
	t_vector	light = vector_normalize(TEST_LIGHT);
	double		ambient;
	
	hit_point = vector_add(ray.origin, vector_multiply(ray.direction, rtx()->closest_point));
	normal = vector_normalize(vector_subtract(hit_point, sphere.pos));
	ambient = TEST_AMBIENT;
	intensity = fmax(vector_dot(normal, light), 0.0) + ambient;
	return (get_rgba(sphere.color, intensity));
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

int	intersect(t_shape shape, t_ray ray, double *t)
{
	if (shape.type == SPHARE)
		intersect_sphare(ray, shape, t);
	else if (shape.type == PLANE)
	{
		//plane function
	}
	if (*t < 0)
		return (0);
	return (*t > 0);
}

int trace_ray(t_ray ray)
{
	double	t;
	t_list	*shapes;
	t_shape	shape;
	t_shape	closest_shape;

	rtx()->closest_point = DBL_MAX;
	ft_bzero(&closest_shape, sizeof(t_shape));
	t = 0.0;
	shapes = rtx()->shapes;
	while (shapes)
	{
		shape = *(t_shape *)shapes->content;
		if (intersect(shape, ray, &t))
		{
			if (t < rtx()->closest_point)
			{
				rtx()->closest_point = t;
				closest_shape = shape;
			}
		}
		shapes = shapes->next;
	}
	if (closest_shape.type == NOTHING)
		return (TEST_BG);
	return (get_pixel_color(ray, closest_shape));
}

void	render_scene(void)
{
	t_ray	ray;
	int		color;
	int		x;
	int		y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			ray = generate_ray(x, y);
			color = trace_ray(ray);
			mlx_put_pixel(rtx()->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	get_shapes(void)
{
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE2)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE3)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE4)));
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
	get_shapes();
	render_scene();
	mlx_loop(rtx()->mlx);
	mlx_terminate(rtx()->mlx);
	return (0);
}
