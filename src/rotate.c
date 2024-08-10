#include <miniRT.h>

/*
Rodrigues' rotation formula
v_rotated = v * cos(θ) + (k × v) * sin(θ) + k * (k · v) * (1 - cos(θ))
*/
t_vector	vector_rotate(t_vector v, t_vector axis, double angle)
{
	t_vector	result;
	double		c;
	double		s;
	double		t;

	c = cos(angle);
	s = sin(angle);
	t = 1.0f - c;
	
	result.x =
			v.x * (t * axis.x * axis.x + c) +
			v.y * (t * axis.x * axis.y - s * axis.z) +
			v.z * (t * axis.x * axis.z + s * axis.y);
	result.y =
			v.x * (t * axis.x * axis.y + s * axis.z) +
			v.y * (t * axis.y * axis.y + c) +
			v.z * (t * axis.y * axis.z - s * axis.x);
	result.z =
			v.x * (t * axis.x * axis.z - s * axis.y) +
			v.y * (t * axis.y * axis.z + s * axis.x) +
			v.z * (t * axis.z * axis.z + c);
	return (result);
}

t_vector random_direction()
{
	t_vector	dir;

	dir.x = (double)rand() / RAND_MAX * 2.0 - 1.0;
	dir.y = (double)rand() / RAND_MAX * 2.0 - 1.0;
	dir.z = (double)rand() / RAND_MAX * 2.0 - 1.0;
	return (vector_normalize(dir));
}

double random_angle()
{
	return (double)rand() / RAND_MAX * (M_PI / 2);
}

void	random_rotate(void)
{
	t_list		*shapes;
	t_shape		*shape;
	t_vector	rotation_axis;
	double		rotation_angle;

	shapes = rtx()->shapes;
	rotation_axis = random_direction();
	rotation_angle = random_angle();
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		shape->dir = vector_normalize(vector_rotate(shape->dir, rotation_axis, rotation_angle));
		shape->box = shape->boxfunc(shape);
		shapes = shapes->next;
	}
	printf("\e[7;1HRotated all shapes %.2f degrees around axis {%.2f, %.2f, %.2f}\e[K\n",
		rotation_angle * (180.0 / M_PI),
		rotation_axis.x, rotation_axis.y, rotation_axis.z);
	if (rtx()->bvh)
		free_bvh(rtx()->bvh);
	rtx()->bvh = bvh(rtx()->shapes);
	if (!rtx()->bvh)
		error();
}
