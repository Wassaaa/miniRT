/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:49 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 17:33:14 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	intersect_plane(t_ray *ray, t_shape *plane, double *t)
{
	double		denominator;
	double		numerator;
	t_vector	oc;

	denominator = vector_dot(ray->direction, plane->dir);
	if (fabs(denominator) < EPSILON)
		return (0);
	oc = vector_subtract(plane->pos, ray->origin);
	numerator = vector_dot(oc, plane->dir);
	*t = numerator / denominator;
	return (*t > 0.0);
}
