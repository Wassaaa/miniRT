#include <miniRT.h>

static double	calculate_t(double box_min, double box_max,
						double ray_origin, double ray_inv_dir)
{
	double	t_min;
	double	t_max;

	t_min = (box_min - ray_origin) * ray_inv_dir;
	t_max = (box_max - ray_origin) * ray_inv_dir;

	return (fmax(fmin(t_min, t_max), 0.0));
}

static double	update_t(double t, double new_t)
{
	double	t_min;
	double	t_max;

	t_min = fmax(t, new_t);
	t_max = new_t;

	return (fmin(t_min, t_max));
}

bool	intersect_aabb(t_ray ray, t_aabb box, double max_t)
{
	double	t;
	double	new_t;

	t = calculate_t(box.min.x, box.max.x,
				ray.origin.x, ray.inv_dir.x);
	new_t = calculate_t(box.min.y, box.max.y,
				ray.origin.y, ray.inv_dir.y);
	t = update_t(t, new_t);
	new_t = calculate_t(box.min.z, box.max.z,
				ray.origin.z, ray.inv_dir.z);
	t = update_t(t, new_t);

	return (t < max_t);
}