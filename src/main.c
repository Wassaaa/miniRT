#include <miniRT.h>

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}

t_shape	*make_sphere(t_vector pos, double diameter, t_color color)
{
	t_shape		*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHERE;
	sphere->pos = pos;
	sphere->diameter = diameter;
	sphere->radius = sphere->diameter / 2;
	sphere->color = color_from_int(color.r, color.g, color.b);
	sphere->box = box_sphere(*sphere);
	// sphere->texture = mlx_load_png("moon.png");
	sphere->shine = SHINE;
	// sphere->texture = mlx_load_png("hive.png");
	// sphere->texture = mlx_load_png("textures/moon.png");
	// sphere->image = mlx_texture_to_image(rtx()->mlx, sphere->texture);
	// sphere->texture = NULL;
	// sphere->image = NULL;
	sphere->checkerboard = 0;

	return (sphere);
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

bool	intersect(t_shape *shape, t_ray ray, double *t)
{
	bool	hit;

	hit = false;
	if (shape->type == SPHERE)
		hit = intersect_sphere(ray, shape, t);
	else if (shape->type == CYLINDER)
		hit = intersect_cylinder(ray, *shape, t);
	else if (shape->type == CONE)
		hit = intersect_cone(ray, shape, t);
	else if (shape->type == LINE || shape->type == WIREFRAME)
		hit = intersect_aabb_line(ray, shape, t);
	if (*t < 0)
		return (false);
	return (hit && *t > 0);
}

bool	check_unbound(t_ray *ray, t_hit *hit)
{
	t_list	*unbound;
	t_shape	*shape;
	double	distance;

	unbound = rtx()->unbound;
	while (unbound)
	{
		shape = (t_shape *)unbound->content;
		if (shape->type == PLANE)
		{
			if (intersect_plane(*ray, *shape, &distance) && distance < hit->distance)
			{
				if (distance > 0.001 && distance < hit->distance)
				{
					hit->distance = distance;
					hit->shape = shape;
					hit->hit = true;
				}
			}
		}
		unbound = unbound->next;
	}
	return (hit->hit);
}

t_hit	intersect_shape(t_ray ray, t_list *shapes)
{
	t_hit			result;
	double			t;
	t_shape			*shape;

	t = INFINITY;
	result = (t_hit){INFINITY, NULL, false, VV, VV, NULL};
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (intersect(shape, ray, &t))
		{
			if (t < result.distance)
			{
				result.distance = t;
				result.shape = shape;
				result.hit = true;
			}
		}
		shapes = shapes->next;
	}
	return (result);
}

t_color trace_ray (t_ray *ray, int depth)
{
	t_hit	hit;

	hit = (t_hit){INFINITY, NULL, false, VV, VV, NULL};
	if (rtx()->wireframe_bvh && rtx()->wireframe)
		hit.hit |= intersect_bvh(rtx()->wireframe_bvh, *ray, &hit);
	if (rtx()->bvh)
		hit.hit |= intersect_bvh(rtx()->bvh, *ray, &hit);
	hit.hit |= check_unbound(ray, &hit);
	if (!hit.hit)
		return (color_from_hex(TEST_BG));
	return (get_pixel_color(ray, &hit, depth));
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

t_bvh	*make_wireframe(t_bvh *shapes_bvh)
{
	t_list	*wireframe;

	wireframe = NULL;
	generate_aabb_lines(shapes_bvh, 0, &wireframe);
	return (bvh(wireframe));

}
//PLANES to unbound
//SPHERE, CYLINDER to shapes
void	get_shapes(void)
{
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEF)));
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEB)));
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEU)));
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANED)));
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANER)));
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEL)));

	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE)));
	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE2)));
	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE3)));
	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE4)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_cone(TEST_CONE)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_cylinder(TEST_CYLINDER1)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_cylinder(TEST_CYLINDER2)));
	rtx()->bvh = bvh(rtx()->shapes);
	rtx()->wireframe_bvh = make_wireframe(rtx()->bvh);
}

t_light	*make_light(t_vector pos, t_color color, double birght)
{
	t_light	*new_light;

	new_light = ft_calloc(1, sizeof(t_light));
	new_light->pos = pos;
	new_light->color = color_scale(color, 1.0 / 255.0);
	new_light->bright = birght;
	return (new_light);
}

void	get_lights(void)
{
	ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT)));
	// ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT2)));
	// ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT2)));
	// ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT3)));
}

void	start_mlx(void)
{
	ft_bzero(rtx(), sizeof(t_rtx));
	rtx()->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	rtx()->img = mlx_new_image(rtx()->mlx, WIDTH, HEIGHT);
	if (!rtx()->img)
		exit(1);
	rtx()->width = WIDTH;
	rtx()->height = HEIGHT;
	mlx_image_to_window(rtx()->mlx, rtx()->img, 0, 0);
	rtx()->debug_normals = 0;
	}
/*
calculate right and up vectors based on current camera dir and WORLD_UP
WORLD_UP x CAMERA_FORWARD = CAM_RIGHT
CAMERA_FORWARD x CAM_RIGHT = CAM_UP
*/
void	init_camera(void)
{
	t_scene		*scene;

	scene = rtx()->scene;
	scene->camera.pos = TEST_CAM_POS;
	scene->camera.dir = vector_normalize(TEST_CAM_DIR);
	scene->camera.fov = tan((TEST_FOV / 2) * (M_PI / 180.0));
	fix_camera();
}

void	setup_scene(void)
{
	rtx()->seed = (unsigned int)(mlx_get_time() * 1000000);
	rtx()->scene = ft_calloc(1, sizeof(t_scene));
	rtx()->scene->ambient = color_scale(TEST_AMBIENT_COL, 1.0/255.0);
	rtx()->scene->ambient = color_scale(rtx()->scene->ambient, TEST_AMBIENT_INT);
	init_camera();
	get_shapes();
	get_lights();
}

void	loop_hook(void *data)
{
	(void)data;
	static int		fps = 1;
	static double	i = 0;
	t_camera		camera;

	camera = rtx()->scene->camera;
	i += rtx()->mlx->delta_time;
	fps++;
	if (i >= 1)
	{
		printf("\e[1;1Hfps [%d]\e[K\n", fps);
		i = 0;
		fps = 0;
	}
	printf("\e[2;1HLast Frame [%.0fms]\e[K\n", rtx()->mlx->delta_time * 1000);

	printf("\e[4;1HFOV [%.2f]\e[K\n", camera.fov);
	printf("\e[5;1HCamera position [{%.2f, %.2f, %.2f}]\e[K\n", camera.pos.x, camera.pos.y, camera.pos.z);
	printf("\e[6;1HCamera direction [{%.2f, %.2f, %.2f}]\e[K\n", camera.dir.x, camera.dir.y, camera.dir.z);
	printf("\e[7;1HCache Hits [%d]\e[K\n", rtx()->cache_hits);
}

void	fix_camera(void)
{
	t_scene	*scene;

	scene = rtx()->scene;
	scene->camera.right = vector_cross(WORLD_UP, scene->camera.dir);
	scene->camera.right = vector_normalize(scene->camera.right);
	scene->camera.up = vector_cross(scene->camera.dir, scene->camera.right);
	scene->camera.up = vector_normalize(scene->camera.up);
}
void	render(void)
{
	render_multi_threaded();
	// render_scene();
}

int	main(void)
{
	start_mlx();
	setup_scene();
	render();
	mlx_key_hook(rtx()->mlx, key_hook, NULL);
	mlx_loop_hook(rtx()->mlx, loop_hook, NULL);
	mlx_loop(rtx()->mlx);
	mlx_terminate(rtx()->mlx);
	return (0);
}

