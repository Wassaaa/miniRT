/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:51:47 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:28:40 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_vector	check_dir(t_vector dir)
{
	if (dir.x > 1 || dir.y > 1 || dir.z > 1
		|| dir.x < -1 || dir.y < -1 || dir.z < -1)
		printf(ERR_DIR_INPUT);
	if (vector_length(dir) != 1)
	{
		printf(ERR_DIR_NOT_NORM);
		return (vector_normalize(dir));
	}
	return (dir);
}

int	check_vector(char *str)
{
	char	**components;

	if (ft_char_count(str, ',') > 2)
		error(E_PARSER, ERR_VEC_FORMAT);
	components = ft_safe_split(str, ",");
	if (array_len(components) != 3)
		error(E_PARSER, ERR_VEC_FORMAT);
	if (!check_float(components[0]) || !check_float(components[1])
		|| !check_float(components[2]))
		error(E_PARSER, ERR_VEC_VALUE);
	return (1);
}

int	check_color(char *str)
{
	char	**components;
	int		i;

	if (ft_char_count(str, ',') > 2)
		error(E_PARSER, ERR_COLOR_FORMAT);
	components = ft_safe_split(str, ",");
	i = 0;
	if (array_len(components) != 3)
		error(E_PARSER, ERR_COLOR_FORMAT);
	while (i < 3)
	{
		if (!check_int(components[i]))
			error(E_PARSER, ERR_COLOR_FORMAT);
		if (ft_atoi(components[i]) < 0 || ft_atoi(components[i]) > 255)
			error(E_PARSER, ERR_COLOR_FORMAT);
		i++;
	}
	return (1);
}

void	check_ac(int check[2])
{
	if (check[0] == 0)
		error(E_PARSER, ERR_NO_AMBIENT);
	if (check[0] > 1)
		error(E_PARSER, ERR_MULTI_AMBIENT);
	if (check[1] == 0)
		error(E_PARSER, ERR_NO_CAMERA);
	if (check[1] > 1)
		error(E_PARSER, ERR_MULTI_CAMERA);
}
