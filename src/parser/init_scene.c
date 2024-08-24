#include <miniRT.h>

void	set_ambient(char **element)
{
	double	amb_light;

	// if (!check_float(element[1]) || !check_color(element[2])))
	// 	error_exit(); //need to free
	if (array_len(element) != 3 || !check_float(element[1]) || !check_color(element[2]))
		free_parser(element, "Wrong ambient setup!");
		//error_exit("Wrong ambient setup!"); //need to free
	amb_light = ft_atof(element[1]);
	check_range_double(amb_light, 0.0, 1.0, "Wrong ambient lighting ratio! Range:[0.0, 1.0]");
	rtx()->ambient = color_scale(parse_color(element[2]), 1.0/255.0);
	rtx()->ambient = color_scale(rtx()->ambient, amb_light);
}

void	set_camera(char **element)
{
	t_camera	*camera;
	t_vector	dir;
	int			fov;

	printf("%d", array_len(element));
	if (array_len(element) != 4 || !check_vector(element[1]) || !check_vector(element[2]) || !check_int(element[3]))
		free_parser(element, "Wrong camera setup!"); //need to free
	camera = &(rtx()->camera);
	camera->pos = parse_vector(element[1], false);
	dir = parse_vector(element[2], true);
	camera->dir = check_dir(dir);
	fov = ft_atoi(element[3]);
	check_range_int(fov, 0, 180, "Wrong horizontal field of view! Range:[0,180]");
	camera->fov = tan((fov * 0.5) * (M_PI / 180.0));
	fix_camera();
}

void	set_light(char **element)
{
	t_light	*light;

	if (array_len(element) != 4 || !check_vector(element[1]) || !check_float(element[2]) || !check_color(element[3]))
		free_parser(element, "Wrong light setup!"); //need to free
	light = ft_calloc(1, sizeof(t_light));
	light->pos = parse_vector(element[1], false);
	light->bright = ft_atof(element[2]);
	check_range_double(light->bright, 0.0, 1.0, "Wrong light brightness ratio! Range:[0.0,1.0]");
	light->color = color_scale(parse_color(element[3]), 1.0/255.0);
	ft_lstadd_back(&rtx()->lights, ft_lstnew(light));
}
