#include <miniRT.h>

void	sphere_uv(t_vector normal, double *u, double *v, int repeat)
{
	double	phi;
	double	theta;
	
	phi = atan2(normal.z, normal.x);
	theta = asin(normal.y);
	*u = (phi + M_PI) / (2 * M_PI);
	*v = 1 - (theta + M_PI / 2) / M_PI;
	*u *= repeat;
	*v *= repeat;
	*u = fmod(*u, 1.0);
	*v = fmod(*v, 1.0);
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
}
void plane_uv(t_vector normal, t_vector point, double *u, double *v)
{
	t_vector	u_axis;
	t_vector	v_axis;

	// Create a coordinate system on the plane
	u_axis = vector_normalize(vector_cross(normal, WORLD_RIGHT));
	if (!u_axis.x && !u_axis.y && !u_axis.z)
		u_axis = vector_normalize(vector_cross(normal, WORLD_UP));
	v_axis = vector_normalize(vector_cross(normal, u_axis));

	u_axis = vector_scale(u_axis, SCALE_PLANE);
	v_axis = vector_scale(v_axis, SCALE_PLANE);
	// Calculate UV coordinates
	*u = vector_dot(u_axis, point);
	*v = vector_dot(v_axis, point);

	// Ensure UV values are wrapped within [0, 1]
	*u = *u - floor(*u);
	*v = *v - floor(*v);
}

void	cylinder_uv(t_vector point, t_vector axis, double height, double *u, double *v)
{
	t_vector normalized_point = vector_normalize(point);
	double theta = atan2(normalized_point.z, normalized_point.x);
	
	*u = 1 - (theta + M_PI) / (2 * M_PI);
	*v = fmod(vector_dot(point, axis) / height, 1.0);
	
	if (*v < 0)
		*v += 1.0;
}

void	cone_uv(t_vector point, t_vector apex, t_vector axis, double height, double *u, double *v)
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
