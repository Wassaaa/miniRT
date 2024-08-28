/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:50 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:18:36 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

bool	intersect_aabb(t_ray ray, t_aabb box, double max_t)
{
	double	t1;
	double	t2;
	double	t_min;
	double	t_max;

	t1 = (box.min.x - ray.origin.x) * ray.inv_dir.x;
	t2 = (box.max.x - ray.origin.x) * ray.inv_dir.x;
	t_min = fmin(t1, t2);
	t_max = fmax(t1, t2);
	t1 = (box.min.y - ray.origin.y) * ray.inv_dir.y;
	t2 = (box.max.y - ray.origin.y) * ray.inv_dir.y;
	t_min = fmax(t_min, fmin(t1, t2));
	t_max = fmin(t_max, fmax(t1, t2));
	t1 = (box.min.z - ray.origin.z) * ray.inv_dir.z;
	t2 = (box.max.z - ray.origin.z) * ray.inv_dir.z;
	t_min = fmax(t_min, fmin(t1, t2));
	t_max = fmin(t_max, fmax(t1, t2));
	return (t_max >= fmax(0.0, t_min) && t_min < max_t);
}
