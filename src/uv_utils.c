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

void	create_local_system(t_shape *shape)
{
	t_vector	u_axis;
	t_vector	v_axis;
	t_vector	normal;

	normal = shape->dir;
	u_axis = vector_cross(normal, WORLD_UP);
	if (vector_length(u_axis) < EPSILON)
		u_axis = vector_cross(normal, WORLD_RIGHT);
	u_axis = vector_normalize(u_axis);
	v_axis = vector_normalize(vector_cross(normal, u_axis));
	shape->u_axis = u_axis;
	shape->v_axis = v_axis;
}