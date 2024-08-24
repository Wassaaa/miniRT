#include <miniRT.h>

void	set_sphere(char	**element)
{
	t_shape			*sphere;

	check_vector(element[1]);
	check_float(element[2]);
	check_color(element[3]);
	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHERE;
	sphere->pos = parse_vector(element[1], false);
	sphere->dir = WORLD_UP;
	sphere->diameter = ft_atof(element[2]);
	check_range_double(sphere->diameter, 0.0, DBL_MAX, ERR_SPHERE_DIAM);
	sphere->radius = sphere->diameter * 0.5;
	sphere->color = color_scale(parse_color(element[3]), 1.0/255.0);
	sphere->boxfunc = box_sphere;
	sphere->box = sphere->boxfunc(sphere);
	if (array_len(element) > 4)
		parse_bonus(element + 4, sphere);
	create_local_system(sphere);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(sphere));
}

void	set_plane(char	**element)
{
	t_shape		*plane;
	t_vector	dir;

	check_vector(element[1]);
	check_vector(element[2]);
	check_color(element[3]);
	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = PLANE;
	plane->pos = parse_vector(element[1], false);
	dir = parse_vector(element[2], true);
	plane->dir = check_dir(dir);
	plane->color = color_scale(parse_color(element[3]), 1.0/255.0);
	if (array_len(element) > 4)
		parse_bonus(element + 4, plane);
	create_local_system(plane);
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(plane));
}

void	set_cylinder(char **element)
{
	t_shape		*cylinder;
	t_vector	dir;

	check_vector(element[1]);
	check_vector(element[2]);
	check_float(element[3]);
	check_float(element[4]);
	check_color(element[5]);
	cylinder = ft_calloc(1, sizeof(t_shape));
	cylinder->type = CYLINDER;
	cylinder->pos = parse_vector(element[1], false);
	dir = parse_vector(element[2], true);
	cylinder->dir = check_dir(dir);
	cylinder->diameter = ft_atof(element[3]);
	check_range_double(cylinder->diameter, 0.0, DBL_MAX, ERR_CYL_DIAM);
	cylinder->radius = cylinder->diameter * 0.5;
	cylinder->height= ft_atof(element[4]);
	cylinder->half_height = cylinder->height / 2;
	check_range_double(cylinder->height, 0.0, DBL_MAX, ERR_CYL_HEIGHT);
	cylinder->color = color_scale(parse_color(element[5]), 1.0/255.0);
	cylinder->boxfunc = box_cylinder;
	cylinder->box = cylinder->boxfunc(cylinder);
	if (array_len(element) > 4)
		parse_bonus(element + 4, cylinder);
	create_local_system(cylinder);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(cylinder));
}

void	set_cone(char **element)
{
	t_shape		*cone;
	t_vector	dir;

	check_vector(element[1]);
	check_vector(element[2]);
	check_float(element[3]);
	check_float(element[4]);
	check_color(element[5]);
	cone = ft_calloc(1, sizeof(t_shape));
	cone->type = CONE;
	cone->pos = parse_vector(element[1], false);
	dir = parse_vector(element[2], true);
	cone->dir = check_dir(dir);
	cone->diameter = ft_atof(element[3]);
	check_range_double(cone->diameter, 0.0, DBL_MAX, ERR_CONE_DIAM);
	cone->radius = cone->diameter * 0.5;
	cone->height= ft_atof(element[4]);
	check_range_double(cone->height, 0.0, DBL_MAX, ERR_CONE_HEIGHT);
	cone->half_angle = atan(cone->radius / cone->height);
	cone->tan_half_angle = tan(cone->half_angle);
	cone->cos_theta = 1.0 / sqrt(1 + cone->tan_half_angle * cone->tan_half_angle);
	cone->sin_theta = cone->tan_half_angle * cone->cos_theta;
	cone->color = color_scale(parse_color(element[5]), 1.0/255.0);
	cone->boxfunc = box_cone;
	cone->box = cone->boxfunc(cone);
	if (array_len(element) > 4)
		parse_bonus(element + 4, cone);
	create_local_system(cone);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(cone));
}
