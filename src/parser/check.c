#include <miniRT.h>

void	check_range_int(int value, int min, int max, char *err_msg)
{
	if (value < min || value > max)
		error(E_PARSER, err_msg);
}

void	check_range_double(double value, double min, double max, char *err_msg)
{
	if (value < min || value > max)
		error(E_PARSER, err_msg);
}

t_vector	check_dir(t_vector dir)
{
	if (dir.x > 1 || dir.y > 1 || dir.z > 1 || dir.x < -1 || dir.y < -1 || dir.z < -1)
		printf(ERR_DIR_INPUT);
	if (vector_length(dir) != 1)
	{
		printf(ERR_DIR_NOT_NORM);
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
			error(E_PARSER, ERR_FLOAT_NO_DIGIT);
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
		error(E_PARSER, ERR_FLOAT_MULTI_DOT);
	return (1);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			error(E_PARSER, ERR_INVALID_INT);
		i++;
	}
	return (1);
}

int	check_vector(char *str)
{
	char	**components;
	
	components = ft_safe_split(str, ",");
	if (array_len(components) != 3)
		error(E_PARSER, ERR_VEC_FORMAT);
	if (!check_float(components[0]) || !check_float(components[1]) || !check_float(components[2]))
		error(E_PARSER, ERR_VEC_VALUE);
	return (1);
}

int	check_color(char *str)
{
	char	**components;
	int		i;
	
	components = ft_safe_split(str, ",");
	i = 0;
	if (array_len(components) != 3)
		error(E_PARSER, ERR_COLOR_FORMAT);
	while (i < 3)
	{
		if (!check_float(components[i]))
			error(E_PARSER, ERR_COLOR_FORMAT);
		if (ft_atoi(components[i]) < 0 || ft_atoi(components[i]) > 255)
			error(E_PARSER, ERR_COLOR_FORMAT);
		i++;
	}
	return (1);
}
