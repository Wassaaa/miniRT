/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:51 by jtu               #+#    #+#             */
/*   Updated: 2024/08/30 12:16:51 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_ambient(char **element)
{
	double	amb_light;

	if (array_len(element) != 3 || !check_float(element[1])
		|| !check_color(element[2]))
		error(E_PARSER, ERR_AMBIENT_SETUP);
	amb_light = ft_atof(element[1]);
	check_range_double(amb_light, 0.0, 1.0, ERR_AMBIENT_RATIO);
	rtx()->ambient = color_scale(parse_color(element[2]), 1.0 / 255.0);
	rtx()->ambient = color_scale(rtx()->ambient, amb_light);
}

void	parse_camera(char **element)
{
	t_camera	*camera;
	t_vector	dir;
	int			fov;

	if (array_len(element) != 4 || !check_vector(element[1])
		|| !check_vector(element[2]) || !check_int(element[3]))
		error(E_PARSER, ERR_CAM_SETUP);
	camera = &(rtx()->camera);
	camera->pos = parse_vector(element[1], false);
	dir = parse_vector(element[2], true);
	camera->dir = check_dir(dir);
	fov = ft_atoi(element[3]);
	check_range_int(fov, 0, 180, ERR_FOV_RANGE);
	camera->fov = tan((fov * 0.5) * (M_PI / 180.0));
	fix_camera();
}

void	parse_light(char **element)
{
	t_light	*light;

	if ((array_len(element) != 3 && array_len(element) != 4)
		|| !check_vector(element[1])
		|| !check_float(element[2])
		|| (array_len(element) == 4 && !check_color(element[3])))
		error(E_PARSER, ERR_LIGHT_SETUP);
	light = ft_calloc(1, sizeof(t_light));
	light->pos = parse_vector(element[1], false);
	light->bright = ft_atof(element[2]);
	check_range_double(light->bright, 0.0, 1.0, ERR_LIGHT_BRIGHT);
	if (element[3])
		light->color = color_scale(parse_color(element[3]), 1.0 / 255.0);
	else
		light->color = (t_color){1, 1, 1};
	ft_lstadd_back(&rtx()->lights, ft_lstnew(light));
}
