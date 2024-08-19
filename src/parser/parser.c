#include <miniRT.h>

void	error_exit(char *err_msg)
{
	perror("Error\n");
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	check_range_int(int value, int min, int max, char *err_msg)
{
	if (value < min || value > max)
		error_exit(err_msg);
}
void	check_range_double(double value, double min, double max, char *err_msg)
{
	if (value < min || value > max)
		error_exit(err_msg);
}

t_vector	check_dir(t_vector dir)
{
	if (dir.x > 1 || dir.y > 1 || dir.z > 1 || dir.x < -1 || dir.y < -1 || dir.z < -1)
		printf("Wrong direction input");
	if (vector_length(dir) != 1)
	{
		printf("Dirction is not normalized");
		return (vector_normalize(dir));
	}
	return (dir);
}

char	**split_line(char *line)
{
	char **element;

	line = ft_strtrim(line, " \t\n");
	if (*line == '\0' || *line == '\n')
		return (NULL);
	element = ft_split(line, '\t'); //need to free later
	return (element);
}

t_color	parse_color(char *color_str)
{
	char	**components;
	t_color	color;
	
	components = ft_split(color_str, ','); //need to free later
	color.r = ft_atoi(components[0]);
	color.g = ft_atoi(components[1]);
	color.b = ft_atoi(components[2]);
	check_range_int(color.r, 0, 255, "Wrong Red value! Range:[0, 255]");
	check_range_int(color.g, 0, 255, "Wrong Green value! Range:[0, 255]");
	check_range_int(color.b, 0, 255, "Wrong Blue value! Range:[0, 255]");
	return (color);
}

t_vector	parse_vector(char *vector_str)
{
	char		**components;
	t_vector	vector;
	
	components = ft_split(vector_str, ','); //need to free later
	vector.x = ft_atof(components[0]);
	vector.y = ft_atof(components[1]);
	vector.z = ft_atof(components[2]);
	return (vector);
}

void	parse_bonus(char **element, t_shape	*shape)
{
	int	len;

	while (*element)
	{
		len = ft_strlen(*element);
		if (ft_strncmp(*element, "chk:1", 6) == 0)
			shape->checkerboard = make_checkerboard(shape->color);
		if (ft_strncmp(*element, "tex:", 4) == 0)
		{
			if (len < 5 || ft_strncmp(*element + len - 4, ".png", 5))
				error_exit("Wrong texture format!");
			shape->texture = png_to_image(rtx()->mlx, *element + 4, true);
		}
		if (ft_strncmp(*element, "bmp:", 4) == 0)
		{
			if (len < 5 || ft_strncmp(*element + len - 4, ".png", 5))
				error_exit("Wrong bump map format!");
			shape->bump = png_to_image(rtx()->mlx, *element + 4, true);
		}
		if (ft_strncmp(*element, "shn:", 4) == 0)
		{
			shape->shine = ft_atoi(*element + 4);
			check_range_int(shape->shine, 0, INT_MAX, "Wrong shine value! Range:[0,INT_MAX]");
		}
		if (ft_strncmp(*element, "ref:", 4) == 0)
		{
			shape->reflectivity = ft_atof(*element + 4);
			check_range_double(shape->reflectivity, 0.0, 1.0, "Wrong reflection value! Range:[0.0,1.0]");
		}
		element++;
	}
}

void	set_ambient(char **element)
{
	double	amb_light;

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

	camera = &(rtx()->camera);
	camera->pos = parse_vector(element[1]);
	dir = parse_vector(element[2]);
	camera->dir = check_dir(dir);
	fov = ft_atoi(element[3]);
	check_range_int(fov, 0, 180, "Wrong horizontal field of view! Range:[0,180]");
	camera->fov = tan((fov * 0.5) * (M_PI / 180.0));
	fix_camera();
}

void	set_light(char **element)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	light->pos = parse_vector(element[1]);
	light->bright = ft_atof(element[2]);
	check_range_double(light->bright, 0.0, 1.0, "Wrong light brightness ratio! Range:[0.0,1.0]");
	light->color = color_scale(parse_color(element[3]), 1.0/255.0);
	ft_lstadd_back(&rtx()->lights, ft_lstnew(light));
}

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	set_sphere(char	**element)
{
	t_shape			*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHERE;
	sphere->pos = parse_vector(element[1]);
	sphere->dir = WORLD_UP;
	sphere->diameter = ft_atof(element[2]);
	check_range_double(sphere->diameter, 0.0, DBL_MAX, "Invalid sphere diameter! Range:[0.0, DBL_MAX]");
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

	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = PLANE;
	plane->pos = parse_vector(element[1]);
	dir = parse_vector(element[2]);
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

	cylinder = ft_calloc(1, sizeof(t_shape));
	cylinder->type = CYLINDER;
	cylinder->pos = parse_vector(element[1]);
	dir = parse_vector(element[2]);
	cylinder->dir = check_dir(dir);
	cylinder->diameter = ft_atof(element[3]);
	check_range_double(cylinder->diameter, 0.0, DBL_MAX, "Invalid cylinder diameter! Range:[0.0, DBL_MAX]");
	cylinder->radius = cylinder->diameter * 0.5;
	cylinder->height= ft_atof(element[4]);
	cylinder->half_height = cylinder->height / 2;
	check_range_double(cylinder->height, 0.0, DBL_MAX, "Invalid cylinder height! Range:[0.0, DBL_MAX]");
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

	cone = ft_calloc(1, sizeof(t_shape));
	cone->type = CONE;
	cone->pos = parse_vector(element[1]);
	dir = parse_vector(element[2]);
	cone->dir = check_dir(dir);
	cone->diameter = ft_atof(element[3]);
	check_range_double(cone->diameter, 0.0, DBL_MAX, "Invalid cone diameter! Range:[0.0, DBL_MAX]");
	cone->radius = cone->diameter * 0.5;
	cone->height= ft_atof(element[4]);
	check_range_double(cone->height, 0.0, DBL_MAX, "Invalid cone height! Range:[0.0, DBL_MAX]");
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

void	parse_element(char **element)
{
	if (ft_strncmp(element[0], "A", 2) == 0)
		set_ambient(element);
	else if (ft_strncmp(element[0],"C", 2) == 0)
		set_camera(element);
	else if (ft_strncmp(element[0], "L", 2) == 0)
		set_light(element);
	else if (ft_strncmp(element[0], "sp", 3) == 0)
		set_sphere(element);
	else if (ft_strncmp(element[0], "pl", 3) == 0)
		set_plane(element);
	else if (ft_strncmp(element[0], "cy", 3) == 0)
		set_cylinder(element);
	else if (ft_strncmp(element[0], "cn", 3) == 0)
		set_cone(element);
}

void print_string_array(char **array) // test function
{
    if (array == NULL)
    {
        printf("Array is NULL\n");
        return;
    }

    int i = 0;
    while (array[i] != 0)
    {
        printf("Element %d: %s\n", i, array[i]);
        i++;
    }
}

void	parse_input(int argc, char *argv[])
{
	size_t	len;
	int		fd;
	char	*line;
	char	**element; //change

	//ft_bzero((void *)element, 10 * sizeof(char *));
	if (argc != 2)
		error_exit("Wrong argument number!");
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error_exit("Wrong input format!");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit("Open failed!");
	line = get_next_line(fd);
	while (line)
	{
		element = split_line(line);
		if (element && *element[0] != '\n' && *element[0] != '#')
		{
			if (element)
				parse_element(element);
		}
		free(line);
		line = get_next_line(fd);
		print_string_array(element);
	}
}
