/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:18 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:20:03 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_color	color_add(t_color c1, t_color c2)
{
	return (color_create(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b));
}

t_color	color_subtract(t_color c1, t_color c2)
{
	return (color_create(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b));
}

t_color	color_multiply(t_color c1, t_color c2)
{
	return (color_create(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b));
}

t_color	color_scale(t_color c, double scale)
{
	return (color_create(c.r * scale, c.g * scale, c.b * scale));
}

t_color	color_clamp(t_color c)
{
	return (color_create(clampd(c.r, 0.0, 1.0), clampd(c.g, 0.0, 1.0),
			clampd(c.b, 0.0, 1.0)));
}
