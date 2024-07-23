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
	double		ambient;
	
	hit_point = vector_add(
		ray.origin,
		vector_multiply(ray.direction, rtx()->closest_point));
	normal = vector_normalize(vector_subtract(hit_point, sphere.pos));
	ambient = rtx()->scene->amb.amb_light;
	intensity = fmax(vector_dot(normal, rtx()->scene->light.dir), ambient);
	return (get_rgba(sphere.color, intensity));
}

/*
calculate right and up vectors based on current camera dir and WORLD_UP
WORLD_UP x CAMERA_FORWARD = CAM_RIGHT
CAMERA_FORWARD x CAM_RIGHT = CAM_UP
*/
t_vector	add_panning(t_vector vector)
{
	t_vector	direction;
	t_vector	right;
	t_vector	up;

	right = vector_cross(WORLD_UP, rtx()->scene->camera.dir);
	up = vector_cross(rtx()->scene->camera.dir, right);
	direction = vector_add(
		vector_multiply(right, vector.x),
		vector_multiply(up, vector.y));
	direction = vector_add(
		direction,
		vector_multiply(rtx()->scene->camera.dir, vector.z));
	rtx()->scene->camera.right = right;
	rtx()->scene->camera.up = up;
	return (direction);
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
	ray.direction = add_panning(vector);
	ray.direction = vector_normalize(ray.direction);
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

void	setup_scene(void)
{
	rtx()->scene = ft_calloc(1, sizeof(t_scene));
	rtx()->scene->amb.amb_light = TEST_AMBIENT;
	rtx()->scene->camera.pos = TEST_CAM_POS;
	rtx()->scene->camera.dir = vector_normalize(TEST_CAM_DIR);
	rtx()->scene->camera.right = TEST_CAM_DIR;
	rtx()->scene->camera.up = TEST_CAM_DIR;
	rtx()->scene->camera.fov = tan((TEST_FOV / 2) * (M_PI / 180.0));
	rtx()->scene->light.pos	= TEST_LIGHT_POS;
	rtx()->scene->light.dir	= vector_normalize(TEST_LIGHT_DIR);
	get_shapes();
}

int	main(void)
{
	start_mlx();
	setup_scene();
	render_scene();
	mlx_key_hook(rtx()->mlx, key_hook, NULL);
	mlx_loop(rtx()->mlx);
	mlx_terminate(rtx()->mlx);
	return (0);
}
