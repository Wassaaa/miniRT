/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:07 by jtu               #+#    #+#             */
/*   Updated: 2024/08/30 12:00:18 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	scale_shape(t_shape *shape, double mult)
{
	shape->diameter *= mult;
	shape->radius = shape->diameter * 0.5;
	shape->height *= mult;
	shape->half_height = shape->height * 0.5;
	shape->box = shape->boxfunc(shape);
	if (shape->type == CONE)
	{
		shape->half_angle = atan(shape->radius / shape->height);
		shape->tan_half = tan(shape->half_angle);
		shape->cos_theta = 1.0 / sqrt(
				1 + shape->tan_half * shape->tan_half);
		shape->sin_theta = shape->tan_half * shape->cos_theta;
		shape->k = 1 + pow(shape->radius / shape->height, 2);
	}
}

bool	scale(t_direction dir)
{
	double	mult;
	t_list	*shapes;
	t_shape	*shape;

	if (rtx()->target > LIM_SCALE)
		return (false);
	if (dir == UP)
		mult = 1.0 + SCALE_STEP;
	else
		mult = 1.0 - SCALE_STEP;
	shapes = rtx()->shapes;
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (shape->type == rtx()->target)
			scale_shape(shape, mult);
		shapes = shapes->next;
	}
	if (rtx()->target < LIM_BVH)
		rebuild_bvh();
	return (true);
}
