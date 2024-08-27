/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:49 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:17:50 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_shape	*make_plane(t_vector pos, t_vector dir, t_color color)
{
	t_shape			*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = PLANE;
	plane->pos = pos;
	plane->dir = check_dir(dir);
	plane->color = color_from_int(color.r, color.g, color.b);
	plane->shine = SHINE;
	plane->reflectivity = 0.7;
	// plane->texture = png_to_texture(rtx()->mlx, "textures/tree.png", false);
	// plane->bump = png_to_texture(rtx()->mlx, "textures/tree.png", true);
	create_local_system(plane);

	return (plane);
}

int	intersect_plane(t_ray *ray, t_shape *plane, double *t)
{
	double denominator;
	double numerator;
	t_vector oc;

	denominator = vector_dot(ray->direction, plane->dir);
	if (fabs(denominator) < EPSILON)
		return (0);
	oc = vector_subtract(plane->pos, ray->origin);
	numerator = vector_dot(oc, plane->dir);
	*t = numerator / denominator;
	return (*t > 0.0);
}
