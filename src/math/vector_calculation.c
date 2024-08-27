/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:16:46 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:28:37 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_vector	vector_min(t_vector a, t_vector b)
{
	return ((t_vector){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z)});
}

t_vector	vector_max(t_vector a, t_vector b)
{
	return ((t_vector){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)});
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
		inv_len = 1.0 / sqrt(length_sq);
		return ((t_vector){a.x * inv_len, a.y * inv_len, a.z * inv_len});
	}
	return (a);
}
