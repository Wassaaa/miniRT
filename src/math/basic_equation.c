/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_equation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:16:46 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:16:47 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

inline t_vector	vector_add(t_vector a, t_vector b)
{
	return (t_vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

inline t_vector	vector_subtract(t_vector a, t_vector b)
{
	return (t_vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

inline t_vector	vector_scale(t_vector a, double scalar)
{
	return (t_vector){a.x * scalar, a.y * scalar, a.z * scalar};
}

inline double	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vector_min(t_vector a, t_vector b)
{
	return ((t_vector){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z)});
}

t_vector	vector_max(t_vector a, t_vector b)
{
	return ((t_vector){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)});
}

inline t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

inline double	vector_length_squared(t_vector a)
{
	return (vector_dot(a, a));
}

inline double	vector_length(t_vector a)
{
	return (sqrt(vector_length_squared(a)));
}

inline t_vector	vector_normalize(t_vector a)
{
	double		length_sq;
	double		inv_len;

	length_sq = a.x * a.x + a.y * a.y + a.z * a.z;
	if (length_sq > 1e-8)
	{
		inv_len = 1.0/sqrt(length_sq);
		return (t_vector){a.x * inv_len, a.y * inv_len, a.z * inv_len};
	}
	return (a);
}
