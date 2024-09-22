/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:58 by jtu               #+#    #+#             */
/*   Updated: 2024/09/22 17:48:31 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_sphere(char	**element)
{
	t_shape	*sphere;

	if (!check_float(element[2]))
		error(E_PARSER, ERR_FLOAT_FORMAT);
	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHERE;
	sphere->pos = parse_vector(element[1], false);
	sphere->dir = (t_vector){0, 1, 0};
	sphere->diameter = ft_atof(element[2]);
	check_range_double(sphere->diameter, 0.0, DBL_MAX, ERR_SPHERE_DIAM);
	sphere->color = color_scale(parse_color(element[3]), 1.0 / 255.0);
	sphere->boxfunc = box_sphere;
	scale_shape(sphere, 1);
	if (array_len(element) > 4)
		parse_bonus(element + 4, sphere);
	if (!sphere->shine)
		sphere->shine = SHINE_SPHERE;
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
	if (!plane->shine)
		plane->shine = SHINE_PLANE;
	create_local_system(plane);
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(plane));
}

void	parse_cylinder(char **element)
{
	t_shape	*cylinder;

	if (!check_float(element[3]) || !check_float(element[4]))
		error(E_PARSER, ERR_FLOAT_FORMAT);
	cylinder = ft_calloc(1, sizeof(t_shape));
	cylinder->type = CYLINDER;
	cylinder->pos = parse_vector(element[1], false);
	cylinder->dir = check_dir(parse_vector(element[2], true));
	cylinder->diameter = ft_atof(element[3]);
	check_range_double(cylinder->diameter, 0.0, DBL_MAX, ERR_CYL_DIAM);
	cylinder->height = ft_atof(element[4]);
	check_range_double(cylinder->height, 0.0, DBL_MAX, ERR_CYL_HEIGHT);
	cylinder->color = color_scale(parse_color(element[5]), 1.0 / 255.0);
	cylinder->boxfunc = box_cylinder;
	scale_shape(cylinder, 1);
	if (array_len(element) > 6)
		parse_bonus(element + 6, cylinder);
	if (!cylinder->shine)
		cylinder->shine = SHINE_CYLINDER;
	create_local_system(cylinder);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(cylinder));
}

void	parse_cone(char **element)
{
	t_shape	*cone;

	if (!check_float(element[3]) || !check_float(element[4]))
		error(E_PARSER, ERR_FLOAT_FORMAT);
	cone = ft_calloc(1, sizeof(t_shape));
	cone->type = CONE;
	cone->pos = parse_vector(element[1], false);
	cone->dir = check_dir(parse_vector(element[2], true));
	cone->dir = vector_scale(cone->dir, -1);
	cone->diameter = ft_atof(element[3]);
	check_range_double(cone->diameter, 0.0, DBL_MAX, ERR_CONE_DIAM);
	cone->height = ft_atof(element[4]);
	check_range_double(cone->height, 0.0, DBL_MAX, ERR_CONE_HEIGHT);
	cone->color = color_scale(parse_color(element[5]), 1.0 / 255.0);
	cone->boxfunc = box_cone;
	scale_shape(cone, 1);
	if (array_len(element) > 6)
		parse_bonus(element + 6, cone);
	if (!cone->shine)
		cone->shine = SHINE_CONE;
	create_local_system(cone);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(cone));
}
