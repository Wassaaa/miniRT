/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:53:45 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:08:22 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_checkerboard(char *element, t_shape *shape)
{
	if (ft_strncmp(element, "chk:1", 6) == 0)
		shape->chk = true;
}

void	parse_texture(char *element, t_shape *shape)
{
	int	len;

	len = ft_strlen(element);
	if (ft_strncmp(element, "tex:", 4) == 0)
	{
		if (len < 5 || ft_strncmp(element + len - 4, ".png", 5))
			error(E_PARSER, ERR_TEXTURE_FORMAT);
		shape->tex_path = ft_strdup(element + 4);
	}
}

void	parse_bump_map(char *element, t_shape *shape)
{
	int	len;

	len = ft_strlen(element);
	if (ft_strncmp(element, "bmp:", 4) == 0)
	{
		if (len < 5 || ft_strncmp(element + len - 4, ".png", 5))
			error(E_PARSER, ERR_BUMP_FORMAT);
		shape->bmp_path = ft_strdup(element + 4);
	}
}

void	parse_shine(char *element, t_shape *shape)
{
	if (ft_strncmp(element, "shn:", 4) == 0)
	{
		check_int(element + 4);
		shape->shine = ft_atoi(element + 4);
		check_range_int(shape->shine, 0, INT_MAX, ERR_SHINE_RANGE);
	}
}

void	parse_reflectivity(char *element, t_shape *shape)
{
	if (ft_strncmp(element, "ref:", 4) == 0)
	{
		shape->reflectivity = ft_atof(element + 4);
		check_range_double(shape->reflectivity, 0.0, 1.0, ERR_REFLECT_RANGE);
	}
}
