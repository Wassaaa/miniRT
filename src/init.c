#include <miniRT.h>

static void	start_mlx(void)
{
	rtx()->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	if (!rtx()->mlx)
		error();
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	rtx()->img = mlx_new_image(rtx()->mlx, WIDTH, HEIGHT);
	if (!rtx()->img)
		error();
	rtx()->width = WIDTH;
	rtx()->height = HEIGHT;
	if (mlx_image_to_window(rtx()->mlx, rtx()->img, 0, 0) == -1)
		error();
}

static void	init_camera(void)
{
	t_scene	*scene;

	scene = rtx()->scene;
	scene->camera.pos = TEST_CAM_POS;
	scene->camera.dir = vector_normalize(TEST_CAM_DIR);
	scene->camera.fov = tan((TEST_FOV / 2) * (M_PI / 180.0));
	fix_camera();
}

static void	init_checkerboard(void)
{
	mlx_image_t	*checkerboard;
	t_color		color;
	t_color		inverted;
	int			i;
	int			j;

	color = color_from_hex(CHECKERB_COLOR);
	inverted = color_subtract(color_create(1, 1, 1), color);
	checkerboard = mlx_new_image(rtx()->mlx, 256, 256);
	if (!checkerboard)
		error();
	i = -1;
	while (++i < 256)
	{
		j = -1;
		while (++j < 256)
		{
			if ((i / 32 + j / 32) % 2 == 0)
				mlx_put_pixel(checkerboard, i, j, color_to_int(inverted));
			else
				mlx_put_pixel(checkerboard, i, j, color_to_int(color));
		}
	}
	rtx()->checkerboard = checkerboard;
}

static void	setup_scene(void)
{
	init_checkerboard();
	rtx()->scene = ft_calloc(1, sizeof(t_scene));
	if (!rtx()->scene)
		error();
	rtx()->scene->ambient = color_scale(TEST_AMBIENT_COL, 1.0/255.0);
	rtx()->scene->ambient = color_scale(rtx()->scene->ambient, TEST_AMBIENT_INT);
	init_camera();
	get_shapes(); //fix allocs
	if (rtx()->bvh)
		free_bvh(rtx()->bvh);
	rtx()->bvh = bvh(rtx()->shapes);
	if (!rtx()->bvh)
		error();
	get_lights(); //fix allocs
}

void	init_rtx(void)
{
	ft_bzero(rtx(), sizeof(t_rtx));
	rtx()->seed = (unsigned int)(mlx_get_time() * 1000000);
	setup_scene();
	start_mlx();
}
