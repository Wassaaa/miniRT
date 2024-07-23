#include <miniRT.h>

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector	vector_scale(t_vector a, double scalar)
{
	t_vector	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

double	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	vector_length(t_vector a)
{
	return (sqrt(vector_dot(a, a)));
}

float fast_inverse_sqrt(float number)
{
	long		i;
	float		x2;
	float		y;
	const float	threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}

t_vector	vector_normalize(t_vector a)
{
	float		inv_length;
	t_vector	result;
	
	inv_length = fast_inverse_sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	result.x = a.x * inv_length;
	result.y = a.y * inv_length;
	result.z = a.z * inv_length;

	return (result);
}

// t_vector	vector_normalize(t_vector a)
// {
// 	t_vector	result;
// 	double		length;

// 	ft_bzero(&result, sizeof(t_vector));
// 	length = vector_length(a);
// 	if (length > 0)
// 	{
// 		result.x = a.x / length;
// 		result.y = a.y / length;
// 		result.z = a.z / length;
// 	}
// 	return (result);
// }
