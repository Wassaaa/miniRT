/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_boxes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:39 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:19:51 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Axis-Aligned Bounding Boxes (AABB)
find the aabb box that can be drawn around a sphere shape
radius_vector represents the distance from the center of the sphere
to any corner of its bounding box in 3D space.
By adding or subtracting this vector from the center,
we reach the corners of the bounding box.
then we compare the new box values with the incoming box and
update the values if needed
*/
t_aabb	box_sphere(t_shape *sphere)
{
	t_vector	radius_vec;
	t_aabb		sphere_box;

	radius_vec = (t_vector){sphere->radius, sphere->radius, sphere->radius};
	sphere_box.min = vector_subtract(sphere->pos, radius_vec);
	sphere_box.max = vector_add(sphere->pos, radius_vec);
	return (sphere_box);
}

t_aabb	box_cylinder(t_shape *cyl)
{
	t_vector	radius_vec;
	t_vector	start;
	t_vector	end;
	t_aabb		cylinder_box;

	start = vector_subtract(
			cyl->pos,
			vector_scale(cyl->dir, cyl->half_height));
	end = vector_add(cyl->pos, vector_scale(cyl->dir, cyl->half_height));
	radius_vec = (t_vector){cyl->radius, cyl->radius, cyl->radius};
	cylinder_box.min = vector_subtract(vector_min(start, end), radius_vec);
	cylinder_box.max = vector_add(vector_max(start, end), radius_vec);
	return (cylinder_box);
}

t_aabb	box_line(t_shape *line)
{
	t_vector	radius_vec;
	t_vector	start;
	t_vector	end;
	t_aabb		line_box;

	start = line->pos;
	end = vector_add(line->pos, line->dir);
	radius_vec = (t_vector){line->radius, line->radius, line->radius};
	line_box.min = vector_subtract(vector_min(start, end), radius_vec);
	line_box.max = vector_add(vector_max(start, end), radius_vec);
	return (line_box);
}

t_aabb	box_cone(t_shape *cone)
{
	t_vector	radius_vec;
	t_vector	start;
	t_vector	end;
	t_aabb		cone_box;

	start = cone->pos;
	end = vector_add(cone->pos, vector_scale(cone->dir, cone->height));
	radius_vec = (t_vector){cone->radius, cone->radius, cone->radius};
	cone_box.min = vector_subtract(vector_min(start, end), radius_vec);
	cone_box.max = vector_add(vector_max(start, end), radius_vec);
	return (cone_box);
}
