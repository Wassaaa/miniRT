#include <miniRT.h>

static void	start_mlx(int width, int height)
{
	rtx()->width = width;
	rtx()->height = height;
	if (!rtx()->mlx)
	{
		rtx()->mlx = mlx_init(width, height, "miniRT", 1);
		if (!rtx()->mlx)
			error();
	}
	if (rtx()->img)
		mlx_delete_image(rtx()->mlx, rtx()->img);
	rtx()->img = mlx_new_image(rtx()->mlx, width, height);
	if (!rtx()->img)
		error();
}

// static void	init_camera(void)
// {
// 	t_camera	*camera;

// 	camera = &(rtx()->camera);
// 	camera->pos = TEST_CAM_POS;
// 	camera->dir = vector_normalize(TEST_CAM_DIR);
// 	camera->fov = tan((TEST_FOV * 0.5) * (M_PI / 180.0));
// 	fix_camera();
// }

void	setup_scene(void)
{
	rtx()->checkerboard = make_checkerboard(color_from_hex(CHECKERB_COLOR));
	// init_camera();
	// get_shapes(); //fix allocs
	if (rtx()->bvh)
		free_bvh(rtx()->bvh);
	rtx()->bvh = bvh(rtx()->shapes);
	if (!rtx()->bvh)
		error();
	//get_lights(); //fix allocs
}

void	init_ui(void)
{
	int	i;

	rtx()->ui[SPHERE] = mlx_put_string(rtx()->mlx, "SPHERE", 0, 0);
	rtx()->ui[CYLINDER] = mlx_put_string(rtx()->mlx, "CYLINDER", 0, 0);
	rtx()->ui[CONE] = mlx_put_string(rtx()->mlx, "CONE", 0, 0);
	rtx()->ui[PLANE] = mlx_put_string(rtx()->mlx, "PLANE", 0, 0);
	rtx()->ui[LIGHT] = mlx_put_string(rtx()->mlx, "LIGHT", 0, 0);
	i = 0;
	while (i < SHAPE_NUM)
	{
		if (!rtx()->ui[i])
			error();
		rtx()->ui[i]->enabled = false;
		i++;
	}
	//get_lights(); //fix allocs
	change_target();
}

void	init_rtx(void)
{
	ft_bzero(rtx(), sizeof(t_rtx));
	start_mlx(WIDTH, HEIGHT);
	rtx()->seed = (unsigned int)(mlx_get_time() * 1000000);
	// setup_scene();
	if (mlx_image_to_window(rtx()->mlx, rtx()->img, 0, 0) == -1)
		error();
	init_ui();
}
