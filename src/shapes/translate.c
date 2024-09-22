/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:12 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:26:34 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
move an object based on current camera direction
*/
void	translate_vector(t_vector *object, t_direction dir)
{
	t_camera	*camera;

	camera = &(rtx()->camera);
	if (dir == UP)
		*object = vector_add(
				*object, vector_scale(camera->up, MOVE_SPEED));
	if (dir == RIGHT)
		*object = vector_add(
				*object, vector_scale(camera->right, MOVE_SPEED));
	if (dir == DOWN)
		*object = vector_add(
				*object, vector_scale(camera->up, -MOVE_SPEED));
	if (dir == LEFT)
		*object = vector_add(
				*object, vector_scale(camera->right, -MOVE_SPEED));
	if (dir == FORWARD)
		*object = vector_add(
				*object, vector_scale(camera->dir, MOVE_SPEED));
	if (dir == BACK)
		*object = vector_add(
				*object, vector_scale(camera->dir, -MOVE_SPEED));
}

void	move_shapes(t_direction dir)
{
	t_list	*shapes;
	t_shape	*shape;

	shapes = rtx()->shapes;
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (shape->type == rtx()->target)
		{
			translate_vector(&shape->pos, dir);
			shape->box = shape->boxfunc(shape);
		}
		shapes = shapes->next;
	}
	if (rtx()->target < LIM_BVH)
		rebuild_bvh();
}

static void	move_list(t_list *objects, t_direction dir)
{
	t_shape	*object;

	while (objects)
	{
		object = (t_shape *)objects->content;
		translate_vector(&object->pos, dir);
		objects = objects->next;
	}
}

static void	move_lights(t_direction dir)
{
	t_list	*lights;
	t_light	*light;

	lights = rtx()->lights;
	while (lights)
	{
		light = (t_light *)lights->content;
		translate_vector(&light->pos, dir);
		lights = lights->next;
	}
}

void	move_objects(t_direction dir)
{
	t_shape_type	target;

	target = rtx()->target;
	if (target == PLANE)
		move_list(rtx()->unbound, dir);
	else if (target == LIGHT)
		move_lights(dir);
	else
		move_shapes(dir);
}
