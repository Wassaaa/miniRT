#include <miniRT.h>

t_shape	*make_plane(t_vector pos, t_vector dir, t_color color)
{
	t_shape	*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = PLANE;
	plane->pos = pos;
	plane->dir = check_dir(dir);
	plane->color = color_from_int(color.r, color.g, color.b);
	plane->shine = SHINE;

	return (plane);
}

int	intersect_plane(t_ray ray, t_shape plane, double *t)
{
	double denominator;
	double numerator;
	t_vector oc;

	denominator = vector_dot(ray.direction, plane.dir);
	if (fabs(denominator) < 1e-6)
		return (0);
	oc = vector_subtract(plane.pos, ray.origin);
	numerator = vector_dot(oc, plane.dir);
	*t = numerator / denominator;
	return (*t > 1e-6);
}
