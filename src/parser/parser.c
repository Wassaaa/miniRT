
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

void	split_line(char *line, char ***element)
{
	line = ft_strtrim(line, " \t\n");
	if (*line == '\0' || *line == '\n')
		return ;
	*element = ft_split(line, '\t'); //need to free later
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

void	parse_bonus(char *element, t_shape	*shape)
{
	while (*element)
	{
		if (ft_strncmp(*element, "chk:", 4) == 0)
		{

		}
		if (ft_strncmp(*element, "tex:", 4) == 0)
		{

		}
		if (ft_strncmp(*element, "bmp:", 4) == 0)
		{

		}
		if (ft_strncmp(*element, "shn:", 4) == 0)
		{

		}
		if (ft_strncmp(*element, "ref:", 4) == 0)
		{

		}
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
	camera->dir = vector_normalize(check_dir(dir));
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

void	set_sphere(char	**element)
{
	t_shape			*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHERE;
	sphere->pos = parse_vector(element[1]);
	sphere->dir = WORLD_UP;
	sphere->diameter = ft_atof(element[2]);
	sphere->radius = sphere->diameter * 0.5;
	sphere->color = color_scale(parse_color(element[3]), 1.0/255.0);
	sphere->boxfunc = box_sphere;
	sphere->box = sphere->boxfunc(sphere);
	if (array_len(element) > 4)
		parse_bonus(element + 4, sphere);
	sphere->shine = SHINE;
	// sphere->image = png_to_image(rtx()->mlx,"hive.png", false);
	// sphere->image = png_to_image(rtx()->mlx, "textures/smile2.png", false);
	sphere->bump = png_to_image(rtx()->mlx, "textures/bumptest.png", true);
	// sphere->image = rtx()->checkerboard;
	create_local_system(sphere);
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE)));
}


void	parse_element(char **element)
{
	if (element[0][0] == '#')
		return ;
	if (ft_strncmp(element[0], "A", 2) == 0)
		set_ambient(element);
	else if (ft_strncmp(element[0],"C", 2) == 0)
		set_camera(element);
	else if (ft_strncmp(element[0], "L", 2) == 0)
		set_light(element);
	else if (ft_strncmp(element[0], "sp", 3) == 0)
		set_sphere(element);
	// else if (ft_strncmp(element[0], "pl", 3) == 0)
	// 	set_plane();
	// else if (ft_strncmp(element[0], "cy", 3) == 0)
	// 	set_cylinder();
	// else if (ft_strncmp(element[0], "cn", 3) == 0)
	// 	set_cone();
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
		split_line(line, &element);
		if (*element[0] != '\n')
			parse_element(element);
		free(line);
		line = get_next_line(fd);
		print_string_array(element);
	}
}
