#include <miniRT.h>

t_color	parse_color(char *color_str)
{
	char	**components;
	t_color	color;
	
	components = ft_safe_split(color_str, ",");
	color.r = ft_atoi(components[0]);
	color.g = ft_atoi(components[1]);
	color.b = ft_atoi(components[2]);
	return (color);
}

t_vector	parse_vector(char *vector_str, bool dir)
{
	char		**components;
	t_vector	vector;
	
	components = ft_safe_split(vector_str, ",");
	vector.x = ft_atof(components[0]);
	vector.y = ft_atof(components[1]);
	vector.z = ft_atof(components[2]);
	if (dir && fabs(vector.x) < EPSILON && fabs(vector.y) < EPSILON && fabs(vector.z) < EPSILON)
		error(E_PARSER, "Direction can't be zero vector");
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
				error(E_PARSER, "Wrong texture format!");
			shape->tex_path = ft_strdup(*element + 4);
		}
		if (ft_strncmp(*element, "bmp:", 4) == 0)
		{
			if (len < 5 || ft_strncmp(*element + len - 4, ".png", 5))
				error(E_PARSER, "Wrong bump map format!");
			shape->bmp_path = ft_strdup(*element + 4);
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

void	parse_element(char **element, int check[2])
{
	if (ft_strncmp(element[0], "A", 2) == 0 && ++check[0])
		set_ambient(element);
	else if (ft_strncmp(element[0],"C", 2) == 0 && ++check[1])
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

void	check_AC(int check[2])
{
	if (check[0] == 0)
		error(E_PARSER, "No ambient light given");
	if (check[0] > 1)
		error(E_PARSER, "Multiple ambient lights are not allowed!");
	if (check[1] == 0)
		error(E_PARSER, "No camera given");
	if (check[1] > 1)
		error(E_PARSER, "Multiple cameras are not allowed!");
}

void	parse_input(char *argv[])
{
	size_t	len;
	int		fd;
	char	*line;
	char	**element; //change
	int		check[2];

	//ft_bzero((void *)element, 10 * sizeof(char *));
	ft_bzero(check, sizeof(int) * 2);
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error(E_PARSER, ERR_INPUT_FORMAT);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error(E_PARSER, ERR_FILE_OPEN);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		add_to_lal(line);
		element = split_line(line);
		if (element && *element && *element[0] != '\n' && *element[0] != '#')
			parse_element(element, check);
		ft_free((void **)&line);
	}
	close(fd);
	check_AC(check);
}
