#include <miniRT.h>

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
		printf("Wrong direction input!");
	if (vector_length(dir) != 1)
	{
		printf("Direction is not normalized!");
		return (vector_normalize(dir));
	}
	return (dir);
}

int	check_float(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			error_exit("Invalid float! No digits found");
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
		error_exit("Invalid float! Multiple dots");
	return (1);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			error_exit("Invalid integer!");
		i++;
	}
	return (1);
}

int	check_vector(char *str)
{
	char	**components;
	
	components = ft_safe_split(str, ',');
	if (array_len(components) != 3)
		error_exit("Wrong vector format!");
	if (!check_float(components[0]) || !check_float(components[1]) || !check_float(components[2]))
		error_exit("Wrong vector value!");
	return (1);
}

int	check_color(char *str)
{
	char	**components;
	int		i;
	
	components = ft_safe_split(str, ',');
	i = 0;
	if (array_len(components) != 3)
		error_exit("Wrong color format!");
	while (i < 3)
	{
		if (!check_float(components[i]))
			error_exit("Wrong color format!");
		if (ft_atof(components[i]) < 0 || ft_atof(components[i]) > 255)
			error_exit("Wrong color format!");
		i++;
	}
	return (1);
}
