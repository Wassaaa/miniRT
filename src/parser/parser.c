/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:41:11 by jtu               #+#    #+#             */
/*   Updated: 2024/09/23 21:47:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_color	parse_color(char *color_str)
{
	char	**components;
	t_color	color;

	check_color(color_str);
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

	check_vector(vector_str);
	components = ft_safe_split(vector_str, ",");
	vector.x = ft_atof(components[0]);
	vector.y = ft_atof(components[1]);
	vector.z = ft_atof(components[2]);
	if (dir && fabs(vector.x) < EPSILON && fabs(vector.y)
		< EPSILON && fabs(vector.z) < EPSILON)
		error(E_PARSER, ERR_ZERO_VECTOR);
	return (vector);
}

void	parse_bonus(char **element, t_shape	*shape)
{
	while (*element)
	{
		if (ft_strncmp(*element, "chk", 3) == 0)
			parse_checkerboard(*element, shape);
		else if (ft_strncmp(*element, "tex:", 4) == 0)
			parse_texture(*element, shape);
		else if (ft_strncmp(*element, "bmp:", 4) == 0)
			parse_bump_map(*element, shape);
		else if (ft_strncmp(*element, "shn:", 4) == 0)
			parse_shine(*element, shape);
		else if (ft_strncmp(*element, "ref:", 4) == 0)
			parse_reflectivity(*element, shape);
		else
			error(E_PARSER, ERR_ELEMENT);
		element++;
	}
}

void	parse_element(char **element, int check[2])
{
	if (ft_strncmp(element[0], "A", 2) == 0 && ++check[0])
		parse_ambient(element);
	else if (ft_strncmp(element[0], "C", 2) == 0 && ++check[1])
		parse_camera(element);
	else if (ft_strncmp(element[0], "L", 2) == 0)
		parse_light(element);
	else if (ft_strncmp(element[0], "sp", 3) == 0)
		parse_sphere(element);
	else if (ft_strncmp(element[0], "pl", 3) == 0)
		parse_plane(element);
	else if (ft_strncmp(element[0], "cy", 3) == 0)
		parse_cylinder(element);
	else if (ft_strncmp(element[0], "cn", 3) == 0)
		parse_cone(element);
	else
		error(E_PARSER, ERR_ELEMENT);
}

void	parse_input(char *argv[])
{
	size_t	len;
	int		fd;
	char	*line;
	char	**element;
	int		check[2];

	ft_bzero(check, sizeof(int) * 2);
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error(E_PARSER, ERR_INPUT_FORMAT);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error(E_PARSER, ERR_FILE_OPEN);
	line = get_next_line(fd);
	while (line)
	{
		add_to_lal(line);
		element = split_line(line);
		if (element && *element && *element[0] != '\n' && *element[0] != '#')
			parse_element(element, check);
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
	check_ac(check);
}
