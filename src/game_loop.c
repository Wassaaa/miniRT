#include <miniRT.h>

void	move_camera(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		rtx()->scene->camera.pos.x -= 1.0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		rtx()->scene->camera.pos.x += 1.0;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		rtx()->scene->camera.pos.y += 1.0;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		rtx()->scene->camera.pos.y -= 1.0;
}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	(void)param;
	move_camera(keydata);
	render_scene();
}