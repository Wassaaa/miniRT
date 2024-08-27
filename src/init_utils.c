/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:25 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:17:26 by jtu              ###   ########.fr       */
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
	camera->right = vector_cross(WORLD_UP, camera->dir);
	if (vector_length(camera->right) < EPSILON)
		camera->right = vector_cross(WORLD_RIGHT, camera->dir);
	camera->right = vector_normalize(camera->right);
	camera->up = vector_cross(camera->dir, camera->right);
	camera->up = vector_normalize(camera->up);
}

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}
