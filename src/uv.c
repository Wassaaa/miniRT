#include <miniRT.h>

void sphere_uv(t_vector point, double *u, double *v)
{
	double phi = atan2(point.z, point.x);
	double theta = asin(point.y);
	
	*u = 1 - (phi + M_PI) / (2 * M_PI);
	*v = (theta + M_PI / 2) / M_PI;
}

void plane_uv(t_vector point, double *u, double *v)
{
	*u = fmod(point.x, 1.0);
	*v = fmod(point.z, 1.0);
	
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
}

void cylinder_uv(t_vector point, t_vector axis, double height, double *u, double *v)
{
	t_vector normalized_point = vector_normalize(point);
	double theta = atan2(normalized_point.z, normalized_point.x);
	
	*u = 1 - (theta + M_PI) / (2 * M_PI);
	*v = fmod(vector_dot(point, axis) / height, 1.0);
	
	if (*v < 0)
		*v += 1.0;
}

void cone_uv(t_vector point, t_vector apex, t_vector axis, double height, double *u, double *v)
{
	t_vector to_point = vector_subtract(point, apex);
	t_vector projected = vector_subtract(to_point, vector_scale(axis, vector_dot(to_point, axis)));
	
	double theta = atan2(vector_dot(projected, vector_cross(axis, vector_cross(axis, projected))),
						 vector_dot(projected, vector_cross(axis, vector_cross(axis, vector_cross(axis, projected)))));
	
	*u = 1.0 - (theta + M_PI) / (2 * M_PI);
	*v = 1.0 - vector_dot(to_point, axis) / height;

	if (*u < 0) *u += 1.0;
	if (*v < 0) *v += 1.0;
}