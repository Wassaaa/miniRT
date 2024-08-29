/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:25 by jtu               #+#    #+#             */
/*   Updated: 2024/08/30 02:30:34 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
calculate right and up vectors based on current camera dir and WORLD_UP
WORLD_UP x CAMERA_FORWARD = CAM_RIGHT
CAMERA_FORWARD x CAM_RIGHT = CAM_UP
*/
void	fix_camera(void)
{
	t_camera	*camera;

	camera = &(rtx()->camera);
	camera->right = vector_cross((t_vector){0, 1, 0}, camera->dir);
	if (vector_length(camera->right) < EPSILON)
		camera->right = vector_cross((t_vector){1, 0, 0}, camera->dir);
	camera->right = vector_normalize(camera->right);
	camera->up = vector_cross(camera->dir, camera->right);
	camera->up = vector_normalize(camera->up);
}

void	build_images(t_list *shapes)
{
	t_shape	*shape;

	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (shape->tex_path)
		{
			shape->texture = png_to_image(rtx()->mlx, shape->tex_path, false);
			free(shape->tex_path);
			shape->tex_path = NULL;
		}
		if (shape->bmp_path)
		{
			shape->bump = png_to_image(rtx()->mlx, shape->bmp_path, true);
			free(shape->bmp_path);
			shape->bmp_path = NULL;
		}
		if (shape->chk)
			shape->checkerboard = make_checkerboard(shape->color);
		shapes = shapes->next;
	}
}

t_hit	new_hit(void)
{
	static t_hit	hit;
	static bool		init = true;

	if (init)
	{
		ft_bzero(&hit, sizeof(t_hit));
		hit.t = INFINITY;
		init = false;
	}
	return (hit);
}

void	setup_scene(void)
{
	build_images(rtx()->unbound);
	build_images(rtx()->shapes);
	rebuild_bvh();
}

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}
