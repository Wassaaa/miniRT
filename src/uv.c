#include <miniRT.h>

void	uv_repeat_wrap(double *u, double *v, int repeat)
{
	*u *= repeat;
	*v *= repeat;
	*u = fmod(*u, 1.0);
	*v = fmod(*v, 1.0);
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
}

void	sphere_uv(t_vector normal, double *u, double *v, int repeat)
{
	double	phi;
	double	theta;
	
	phi = atan2(normal.z, normal.x);
	theta = asin(normal.y);
	*u = (phi + M_PI) / (2 * M_PI);
	*v = 1 - (theta + M_PI / 2) / M_PI;
	uv_repeat_wrap(u, v, repeat);
}

/*
1. Convert hit point to local coordinates
2. Create a consistent local coordinate system
3. Calculate UV coordinates
*/
void plane_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	u_axis;
	t_vector	v_axis;
	t_vector	local_point;

	local_point = vector_subtract(hit->hit_point, hit->shape->pos);
	u_axis = vector_normalize(vector_cross(hit->shape->dir, WORLD_UP));
	if (vector_length(u_axis) < EPSILON)
		u_axis = vector_normalize(vector_cross(hit->shape->dir, WORLD_RIGHT));
	v_axis = vector_normalize(vector_cross(hit->shape->dir, u_axis));
	*u = vector_dot(u_axis, local_point) * SCALE_PLANE;
	*v = vector_dot(v_axis, local_point) * SCALE_PLANE;
	uv_repeat_wrap(u, v, repeat);
}
/*
1. Create a local coordinate system
2. Project the point onto our local x and y axes
3. Calculate the angle
*/
double	calculate_theta(t_vector proj_point, t_vector axis)
{
	t_vector	x_axis;
	t_vector	y_axis;
	double		x_coord;
	double		y_coord;
	double		theta;

	x_axis = vector_cross(axis, WORLD_UP);
	if (vector_length(x_axis) < EPSILON)
		x_axis = vector_cross(axis, WORLD_RIGHT);
	x_axis = vector_normalize(x_axis);
	y_axis = vector_normalize(vector_cross(axis, x_axis));
	x_coord = vector_dot(proj_point, x_axis);
	y_coord = vector_dot(proj_point, y_axis);
	theta = atan2(y_coord, x_coord);

	return (theta);
}

/*
1. Convert hit point to local coordinates
2. Calculate height along the axis
3. Project the point onto the plane perpendicular to the axis
4. Calculate angle in the projected plane (theta)
5. Calculate UV coordinates
*/
void cylindrical_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	local_point;
	t_vector	proj_point;
	double		theta;
	double		height;

	local_point = vector_subtract(hit->hit_point, hit->shape->pos);
	height = vector_dot(local_point, hit->shape->dir);
	proj_point = vector_subtract(local_point, vector_scale(hit->shape->dir, height));
	theta = calculate_theta(proj_point, hit->shape->dir);
	*u = (theta + M_PI) / (2 * M_PI);
	*v = height / hit->shape->height;
	uv_repeat_wrap(u, v, repeat);
}
