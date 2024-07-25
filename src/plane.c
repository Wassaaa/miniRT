#include <miniRT.h>

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
