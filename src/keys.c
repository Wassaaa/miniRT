/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:35 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:17:36 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	pan_camera(double horizontal_angle, double vertical_angle)
{
	t_camera	*camera;

	camera = &(rtx()->camera);
	camera->dir = vector_rotate(camera->dir, WORLD_UP, horizontal_angle);
	camera->dir = vector_rotate(camera->dir, camera->right, -vertical_angle);
	camera->right = vector_rotate(camera->right, WORLD_UP, horizontal_angle);
	camera->right = vector_rotate(camera->right, camera->right, -vertical_angle);
	camera->up = vector_rotate(camera->up, WORLD_UP, horizontal_angle);
	camera->up = vector_rotate(camera->up, camera->right, -vertical_angle);
}

static void	adjust_fov(int direction)
{
	double current_fov;

	current_fov = 2 * atan(rtx()->camera.fov) * (180.0 / M_PI);
	if (direction > 0)
		current_fov += FOV_STEP;
	else
		current_fov -= FOV_STEP;
	if (current_fov < MIN_FOV)
		current_fov = MIN_FOV;
	else if (current_fov > MAX_FOV)
		current_fov = MAX_FOV;
	rtx()->camera.fov = tan((current_fov * 0.5) * (M_PI / 180.0));
}

static bool	move_camera(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_SPACE && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->camera.pos, UP);
	else if (keydata.key == MLX_KEY_C && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->camera.pos, DOWN);
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->camera.pos, FORWARD);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->camera.pos, LEFT);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->camera.pos, BACK);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->camera.pos, RIGHT);
	else if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS))
		pan_camera(0, PAN_AMOUNT);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		pan_camera(PAN_AMOUNT, 0);
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS))
		pan_camera(0, -PAN_AMOUNT);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		pan_camera(-PAN_AMOUNT, 0);
	else
		return (false);
	return (true);
}

static bool	adjust_shapes(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_RELEASE)
		move_objects(UP);
	else if (keydata.key == MLX_KEY_L && keydata.action == MLX_RELEASE)
		move_objects(DOWN);
	else if (keydata.key == MLX_KEY_U && keydata.action == MLX_RELEASE)
		move_objects(FORWARD);
	else if (keydata.key == MLX_KEY_J && keydata.action == MLX_RELEASE)
		move_objects(BACK);
	else if (keydata.key == MLX_KEY_H && keydata.action == MLX_RELEASE)
		move_objects(LEFT);
	else if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		move_objects(RIGHT);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_RELEASE)
		return (rotate_objects(FORWARD));
	else if (keydata.key == MLX_KEY_T && keydata.action == MLX_RELEASE)
		return (rotate_objects(BACK));
	else if (keydata.key == MLX_KEY_PERIOD && keydata.action == MLX_RELEASE)
		return (scale(UP));
	else if (keydata.key == MLX_KEY_COMMA && keydata.action == MLX_RELEASE)
		return (scale(DOWN));
	else
		return (false);
	return (true);
}

bool	keys(mlx_key_data_t keydata)
{
	if (move_camera(keydata))
		return (true);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_RELEASE)
		return (change_target());
	else if (keydata.key == MLX_KEY_PAGE_UP && keydata.action == MLX_RELEASE)
		adjust_fov(-1);
	else if (keydata.key == MLX_KEY_PAGE_DOWN && keydata.action == MLX_RELEASE)
		adjust_fov(1);
	else if (keydata.key == MLX_KEY_B && keydata.action == MLX_RELEASE)
	{
		rtx()->wireframe = !rtx()->wireframe;
		rtx()->wireframe_bvh = make_wireframe(rtx()->bvh);
		if (!rtx()->wireframe_bvh)
			error(E_MEM, NULL);
	}
	else if (adjust_shapes(keydata))
		return (true);
	else
		return (false);
	return (true);

}


