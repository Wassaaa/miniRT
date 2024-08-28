/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_intersect_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:47 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:18:21 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <wireframe.h>

static inline t_coeff	calc_coefficients(t_ray *ray, t_shape *line)
{
	t_coeff		coeff;
	t_vector	ray_to_line;

	ray_to_line = vector_subtract(line->pos, ray->origin);
	coeff.a = vector_dot(line->dir, line->dir);
	coeff.b = vector_dot(line->dir, ray->direction);
	coeff.c = vector_dot(ray->direction, ray->direction);
	coeff.d = vector_dot(line->dir, ray_to_line);
	coeff.e = vector_dot(ray->direction, ray_to_line);
	return (coeff);
}

static inline double	calc_denominator(t_coeff coeff)
{
	double	denom;

	denom = coeff.a * coeff.c - coeff.b * coeff.b;
	if (fabs(denom) < EPSILON)
		return (0);
	return (1.0 / denom);
}

static inline t_vector	calc_closest_points(t_ray *ray, t_shape *line,
										double line_t, double ray_t)
{
	t_vector	p_on_line;
	t_vector	p_on_ray;

	p_on_line = vector_add(line->pos, vector_scale(line->dir, line_t));
	p_on_ray = vector_add(ray->origin, vector_scale(ray->direction, ray_t));
	return (vector_subtract(p_on_line, p_on_ray));
}

static inline bool	check_intersection(t_coeff *coeff, t_ray *ray,
	t_shape *line, double *t)
{
	t_vector	closest_points;
	double		distance_sq;
	double		line_t;
	double		ray_t;

	line_t = fmin(fmax((coeff->b * coeff->e - coeff->c * coeff->d)
				* coeff->inv_denom, 0), 1);
	ray_t = (coeff->a * coeff->e - coeff->b * coeff->d) * coeff->inv_denom;
	closest_points = calc_closest_points(ray, line, line_t, ray_t);
	distance_sq = vector_length_squared(closest_points);
	if (distance_sq <= line->radius * line->radius + EPSILON)
	{
		*t = ray_t;
		return (true);
	}
	return (false);
}

/**
 * Checks if a ray intersects with an Axis-Aligned
 * Bounding Box (AABB) line segment.
 * 
 * This function uses the closest point approach to determine intersection:
 * 1. Calculate the closest points between the ray and the line segment.
 * 2. Check if these points are within a threshold distance
 * (AABB_LINE_THICKNESS).
 * 
 * The calculations are based on the following formulas:
 * Let R(t) = ray_origin + t * ray_direction be the ray equation
 * Let L(s) = line_start + s * line_direction be the line equation
 * 
 * We minimize the distance between R(t) and L(s):
 * |R(t) - L(s)|^2 = at^2 + bs^2 + 2cts - 2dt - 2es + f
 * 
 * Where:
 * a = ray_direction · ray_direction
 * b = line_direction · line_direction (pre-computed as length_squared)
 * c = ray_direction · line_direction
 * d = ray_direction · (line_start - ray_origin)
 * e = line_direction · (line_start - ray_origin)
 * f = (line_start - ray_origin) · (line_start - ray_origin)
 * 
 * Solving for t and s gives us the closest points on the ray and line.
 * 
 * @param ray The ray to check for intersection
 * @param line The AABB line segment to check against
 * @param t Pointer to store the intersection distance along the ray
 * @return true if an intersection occurs, false otherwise
 */
bool	intersect_aabb_line(t_ray *ray, t_shape *line, double *t)
{
	t_coeff	coeff;

	coeff = calc_coefficients(ray, line);
	coeff.inv_denom = calc_denominator(coeff);
	if (coeff.inv_denom == 0)
		return (false);
	return (check_intersection(&coeff, ray, line, t));
}
