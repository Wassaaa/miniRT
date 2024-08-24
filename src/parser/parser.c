#include <miniRT.h>

t_color	parse_color(char *color_str)
{
	char	**components;
	t_color	color;
	
	components = ft_safe_split(color_str, ","); //need to free later
	color.r = ft_atoi(components[0]);
	color.g = ft_atoi(components[1]);
	color.b = ft_atoi(components[2]);
	free_parser(components, NULL);
	// check_range_int(color.r, 0, 255, "Wrong Red value! Range:[0, 255]");
	// check_range_int(color.g, 0, 255, "Wrong Green value! Range:[0, 255]");
	// check_range_int(color.b, 0, 255, "Wrong Blue value! Range:[0, 255]");
	return (color);
}

t_vector	parse_vector(char *vector_str, bool dir)
{
	char		**components;
	t_vector	vector;
	
	components = ft_safe_split(vector_str, ","); //need to free later
	vector.x = ft_atof(components[0]);
	vector.y = ft_atof(components[1]);
	vector.z = ft_atof(components[2]);
	free_parser(components, NULL);
	if (dir && fabs(vector.x) < EPSILON && fabs(vector.y) < EPSILON && fabs(vector.z) < EPSILON)
		error_exit("Direction can't be zero vector");
	return (vector);
}

void	parse_bonus(char **element, t_shape	*shape)
{
	int	len;

	while (*element)
	{
		len = ft_strlen(*element);
		if (ft_strncmp(*element, "chk:1", 6) == 0)
			shape->chk = true;
		if (ft_strncmp(*element, "tex:", 4) == 0)
		{
			if (len < 5 || ft_strncmp(*element + len - 4, ".png", 5))
				free_parser(element, "Wrong texture format!");
			shape->tex_path = ft_strdup(*element + 4);
		}
		if (ft_strncmp(*element, "bmp:", 4) == 0)
		{
			if (len < 5 || ft_strncmp(*element + len - 4, ".png", 5))
				free_parser(element, "Wrong bump map format!");
			shape->bpm_path = ft_strdup(*element + 4);
			//shape->bump = png_to_image(rtx()->mlx, *element + 4, true);
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

// void print_string_array(char **array) // test function
// {
//     if (array == NULL)
//     {
//         printf("Array is NULL\n");
//         return;
//     }

//     int i = 0;
//     while (array[i] != 0)
//     {
//         printf("Element %d: %s\n", i, array[i]);
//         i++;
//     }
// }

void	parse_input(char *argv[])
{
	size_t	len;
	int		fd;
	char	*line;
	char	**element; //change

	//ft_bzero((void *)element, 10 * sizeof(char *));
	// if (argc != 2)
	// 	error_exit("Wrong argument number!");
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error_exit("Wrong input format!");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit("Open failed!");
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		add_to_lal(line);
		element = split_line(line);
		if (element && *element && *element[0] != '\n' && *element[0] != '#')
			parse_element(element);
		free_parser(element, NULL);
		ft_free((void **)&line);
		//print_string_array(element);
	}
	close(fd);
}
