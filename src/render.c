/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:00 by jtu               #+#    #+#             */
/*   Updated: 2024/09/22 13:35:23 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_color	trace_ray(t_ray *ray, int depth)
{
	t_hit	hit;

	hit = new_hit();
	if (rtx()->wireframe_bvh && rtx()->wireframe)
		hit.hit |= intersect_bvh(rtx()->wireframe_bvh, ray, &hit);
	if (rtx()->bvh)
		hit.hit |= intersect_bvh(rtx()->bvh, ray, &hit);
	hit.hit |= check_unbound(ray, &hit);
	if (!hit.hit)
		return (color_from_hex(BACKGROUND_COLOR));
	return (get_pixel_color(ray, &hit, depth));
}

t_vector	add_panning(t_vector *vector)
{
	t_vector	direction;
	t_vector	right;
	t_vector	up;

	right = rtx()->camera.right;
	up = rtx()->camera.up;
	direction = vector_add(
			vector_scale(right, vector->x),
			vector_scale(up, vector->y));
	direction = vector_add(
			direction,
			vector_scale(rtx()->camera.dir, vector->z));
	return (direction);
}

t_ray	create_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vector_normalize(direction);
	ray.origin = vector_add(origin, vector_scale(ray.direction, EPSILON));
	ray.inv_dir = (t_vector){
		1.0 / ray.direction.x,
		1.0 / ray.direction.y,
		1.0 / ray.direction.z
	};
	return (ray);
}

t_ray	generate_ray(double x, double y)
{
	t_ray		ray;
	t_vector	vector;
	t_camera	*camera;
	double		aspect_ratio;
	double		fov;

	camera = &(rtx()->camera);
	aspect_ratio = (double)rtx()->width / (double)rtx()->height;
	fov = camera->fov;
	vector.x = (2 * (x / rtx()->width) - 1) * fov * aspect_ratio;
	vector.y = (1 - 2 * (y / rtx()->height)) * fov;
	vector.z = 1;
	ray = create_ray(camera->pos, add_panning(&vector));
	return (ray);
}

void	render_scene(void)
{
	t_ray		ray;
	t_color		color;
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < rtx()->height)
	{
		x = 0;
		while (x < rtx()->width)
		{
			ray = generate_ray(x, y);
			color = trace_ray(&ray, REFLECT_DEPTH);
			mlx_put_pixel(rtx()->img, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
}
