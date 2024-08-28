/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:58 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 18:05:19 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_sphere(char	**element)
{
	t_shape	*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHERE;
	sphere->pos = parse_vector(element[1], false);
	sphere->dir = WORLD_UP;
	sphere->diameter = ft_atof(element[2]);
	check_range_double(sphere->diameter, 0.0, DBL_MAX, ERR_SPHERE_DIAM);
	sphere->radius = sphere->diameter * 0.5;
	sphere->color = color_scale(parse_color(element[3]), 1.0 / 255.0);
	sphere->boxfunc = box_sphere;
	sphere->box = sphere->boxfunc(sphere);
	if (array_len(element) > 4)
		parse_bonus(element + 4, sphere);
	create_local_system(sphere);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(sphere));
}

void	parse_plane(char	**element)
{
	t_shape	*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = PLANE;
	plane->pos = parse_vector(element[1], false);
	plane->dir = check_dir(parse_vector(element[2], true));
	plane->color = color_scale(parse_color(element[3]), 1.0 / 255.0);
	if (array_len(element) > 4)
		parse_bonus(element + 4, plane);
	create_local_system(plane);
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(plane));
}

void	parse_cylinder(char **element)
{
	t_shape	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_shape));
	cylinder->type = CYLINDER;
	cylinder->pos = parse_vector(element[1], false);
	cylinder->dir = check_dir(parse_vector(element[2], true));
	cylinder->diameter = ft_atof(element[3]);
	check_range_double(cylinder->diameter, 0.0, DBL_MAX, ERR_CYL_DIAM);
	cylinder->radius = cylinder->diameter * 0.5;
	cylinder->height = ft_atof(element[4]);
	cylinder->half_height = cylinder->height / 2;
	check_range_double(cylinder->height, 0.0, DBL_MAX, ERR_CYL_HEIGHT);
	cylinder->color = color_scale(parse_color(element[5]), 1.0 / 255.0);
	cylinder->boxfunc = box_cylinder;
	cylinder->box = cylinder->boxfunc(cylinder);
	if (array_len(element) > 4)
		parse_bonus(element + 4, cylinder);
	create_local_system(cylinder);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(cylinder));
}

void	parse_cone(char **element)
{
	t_shape	*cone;

	cone = ft_calloc(1, sizeof(t_shape));
	cone->type = CONE;
	cone->pos = parse_vector(element[1], false);
	cone->dir = check_dir(parse_vector(element[2], true));
	cone->diameter = ft_atof(element[3]);
	check_range_double(cone->diameter, 0.0, DBL_MAX, ERR_CONE_DIAM);
	cone->radius = cone->diameter * 0.5;
	cone->height = ft_atof(element[4]);
	check_range_double(cone->height, 0.0, DBL_MAX, ERR_CONE_HEIGHT);
	cone->half_angle = atan(cone->radius / cone->height);
	cone->tan_half_angle = tan(cone->half_angle);
	cone->cos_theta = 1.0 / sqrt(1 + cone->tan_half_angle
			* cone->tan_half_angle);
	cone->sin_theta = cone->tan_half_angle * cone->cos_theta;
	cone->k = 1 + pow(cone->radius / cone->height, 2);
	cone->color = color_scale(parse_color(element[5]), 1.0 / 255.0);
	cone->boxfunc = box_cone;
	cone->box = cone->boxfunc(cone);
	if (array_len(element) > 4)
		parse_bonus(element + 4, cone);
	create_local_system(cone);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(cone));
}