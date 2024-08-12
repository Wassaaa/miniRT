
#include <miniRT.h>

void	error_exit(char *err_msg)
{
	printf("%s",err_msg);
	exit(EXIT_FAILURE);
}

void	split_line(char *line, char **element)
{
	while (*line)
	{
		while (*line == '\n' || *line == '\t')
			line++;
		if (*line == '\0' || *line == '\n')
			break;
		element = ft_split(line, ' '); //need to free later
	}
}

void	parse_element(char **element)
{
	// if (ft_strncmp(element[0], "A", 2) == 0)
	// 	set_ambient();
	// else if (ft_strncmp(element[0],"C", 2) == 0)
	// 	set_camera();
	// else if (ft_strncmp(element[0], "L", 2) == 0)
	// 	set_light(element);
	// else if (ft_strncmp(element[0], "sp", 3) == 0)
	// 	set_sphere();
	// else if (ft_strncmp(element[0], "pl", 3) == 0)
	// 	set_plane();
	// else if (ft_strncmp(element[0], "cy", 3) == 0)
	// 	set_cylinder();
	// else if (ft_strncmp(element[0], "cn", 3) == 0)
	// 	set_cone();
	(void)element;
}

void print_string_array(char **array) // test function
{
    // if (array == NULL)
    // {
    //     printf("Array is NULL\n");
    //     return;
    // }

    // int i = 0;
    // while (array[i] != NULL)
    // {
    //     printf("Element %d: %s\n", i, array[i]);
    //     i++;
    // }
}

void	parse_input(int argc, char *argv[])
{
	size_t	len;
	int		fd;
	char	*line;
	char	*element[10]; //change

	ft_bzero((void *)element, 10 * sizeof(char *));
	if (argc != 2)
		error_exit("Error\nWrong argument number!");
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error_exit("Error\nWrong input format!");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit("Error\nOpen failed!");
	line = get_next_line(fd);
	while (line)
	{
		split_line(line, element);
		if (*element[0] != '\n')
			parse_element(element);
		free(line);
		line = get_next_line(fd);
	}
	print_string_array(element);
}
