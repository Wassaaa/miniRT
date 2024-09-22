/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:53:45 by jtu               #+#    #+#             */
/*   Updated: 2024/09/22 13:43:59 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_checkerboard(char *element, t_shape *shape)
{
	if (ft_strncmp(element, "chk:1", 6) == 0)
		shape->chk = true;
	else if (ft_strncmp(element, "chk:0", 6) == 0)
		shape->chk = false;
	else
		error(E_PARSER, ERR_CHK);
}

void	parse_texture(char *element, t_shape *shape)
{
	int	len;
	int	fd;

	len = ft_strlen(element);
	if (len < 5 || ft_strncmp(element + len - 4, ".png", 5))
		error(E_PARSER, ERR_TEXTURE_FORMAT);
	shape->tex_path = ft_strdup(element + 4);
	fd = open(shape->tex_path, O_RDONLY);
	if (fd < 0)
		error(E_MEM, NULL);
	close(fd);
}

void	parse_bump_map(char *element, t_shape *shape)
{
	int	len;
	int	fd;

	len = ft_strlen(element);
	if (len < 5 || ft_strncmp(element + len - 4, ".png", 5))
		error(E_PARSER, ERR_BUMP_FORMAT);
	shape->bmp_path = ft_strdup(element + 4);
	fd = open(shape->bmp_path, O_RDONLY);
	if (fd < 0)
		error(E_MEM, NULL);
	close(fd);
}

void	parse_shine(char *element, t_shape *shape)
{
	if (!check_int(element + 4))
		error(E_PARSER, ERR_SHINE);
	shape->shine = ft_atoi(element + 4);
	check_range_int(shape->shine, 0, INT_MAX, ERR_SHINE);
}

void	parse_reflectivity(char *element, t_shape *shape)
{
	if (!check_float(element + 4))
		error(E_PARSER, ERR_REFLECT);
	shape->reflectivity = ft_atof(element + 4);
	check_range_double(shape->reflectivity, 0.0, 1.0, ERR_REFLECT);
}
