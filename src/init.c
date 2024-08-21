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
	// init_camera();
	// get_shapes(); //fix allocs
	if (rtx()->bvh)
		free_bvh(rtx()->bvh);
	rtx()->bvh = bvh(rtx()->shapes);
	if (!rtx()->bvh)
		error();
	//get_lights(); //fix allocs
}

static mlx_image_t *safe_mlx_put_string(mlx_t *mlx, char *str)
{
	mlx_image_t	*img;

	img = mlx_put_string(mlx, str, 0, 0);
	if (!img)
		error();
	img->enabled = false;
	return (img);
}

void	init_ui(void)
{
	rtx()->ui[SPHERE] = safe_mlx_put_string(rtx()->mlx, "SPHERE");
	rtx()->ui[CYLINDER] = safe_mlx_put_string(rtx()->mlx, "CYLINDER");
	rtx()->ui[CONE] = safe_mlx_put_string(rtx()->mlx, "CONE");
	rtx()->ui[PLANE] = safe_mlx_put_string(rtx()->mlx, "PLANE");
	rtx()->ui[LIGHT] = safe_mlx_put_string(rtx()->mlx, "LIGHT");
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
