#include <miniRT.h>

/*
Rodrigues' rotation formula
v_rotated = v * cos(θ) + (k × v) * sin(θ) + k * (k · v) * (1 - cos(θ))
*/
t_vector	vector_rotate(t_vector v, t_vector axis, double angle)
{
	t_vector	result;
	double c;
	double s;
	double t;

	c = cos(angle);
	s = sin(angle);
	t = 1.0f - c;
	
	result.x =
			v.x * (t * axis.x * axis.x + c) +
			v.y * (t * axis.x * axis.y - s * axis.z) +
			v.z * (t * axis.x * axis.z + s * axis.y);
	result.y =
			v.x * (t * axis.x * axis.y + s * axis.z) +
			v.y * (t * axis.y * axis.y + c) +
			v.z * (t * axis.y * axis.z - s * axis.x);
	result.z =
			v.x * (t * axis.x * axis.z - s * axis.y) +
			v.y * (t * axis.y * axis.z + s * axis.x) +
			v.z * (t * axis.z * axis.z + c);
	return (result);
}

void	pan_camera(double horizontal_angle, double vertical_angle)
{
	t_camera	*camera;

	camera = &(rtx()->scene->camera);
	camera->dir = vector_rotate(camera->dir, WORLD_UP, horizontal_angle);
	camera->dir = vector_rotate(camera->dir, camera->right, -vertical_angle);
	camera->dir = vector_normalize(camera->dir);
}

void	move_camera(t_direction dir)
{
	t_camera	*camera;

	camera = &(rtx()->scene->camera);
	if (dir == UP)
		camera->pos = vector_add(
			camera->pos,
			vector_multiply(camera->up, MOVE_SPEED));
	if (dir == RIGHT)
		camera->pos = vector_add(
			camera->pos,
			vector_multiply(camera->right, MOVE_SPEED));
	if (dir == DOWN)
		camera->pos = vector_add(
			camera->pos,
			vector_multiply(camera->up, -MOVE_SPEED));
	if (dir == LEFT)
		camera->pos = vector_add(
			camera->pos,
			vector_multiply(camera->right, -MOVE_SPEED));
}

void	camera_adjustment(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		move_camera(UP);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		move_camera(LEFT);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		move_camera(DOWN);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		move_camera(RIGHT);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		pan_camera(0, PAN_AMOUNT);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		pan_camera(PAN_AMOUNT, 0);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		pan_camera(0, -PAN_AMOUNT);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		pan_camera(-PAN_AMOUNT, 0);
	if (keydata.key == MLX_KEY_PAGE_UP && keydata.action == MLX_RELEASE)
		rtx()->scene->camera.fov -= 10;
	if (keydata.key == MLX_KEY_PAGE_DOWN && keydata.action == MLX_RELEASE)
		rtx()->scene->camera.fov += 10;

}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	(void)param;
	camera_adjustment(keydata);
	render_scene();
}