#include <miniRT.h>

t_quadratic_coeffs	calculate_quadratic_coeffs_cylinder(t_ray ray, t_shape shape)
{
	t_quadratic_coeffs	coeffs;
	t_vector oc;
	
	oc = vector_subtract(ray.origin, shape.pos);
	coeffs.a = vector_dot(ray.direction, ray.direction) - 
			pow(vector_dot(ray.direction, shape.dir), 2);
	coeffs.b = 2 * (vector_dot(ray.direction, oc) - 
			vector_dot(ray.direction, shape.dir) * vector_dot(oc, shape.dir));
	coeffs.c = vector_dot(oc, oc) - pow(vector_dot(oc, shape.dir), 2) - 
			shape.radius * shape.radius;
	return (coeffs);
}

int	intersect_cylinder(t_ray ray, t_shape cylinder, double *t)
{
	t_quadratic_coeffs	coeffs;
	double				discriminant;
	//double				intersection;
	double				t_body;
	t_vector			v_caps[2];
	double			t_caps[2];

	coeffs = calculate_quadratic_coeffs_cylinder(ray, cylinder);
	discriminant = (coeffs.b * coeffs.b) - (4 * coeffs.a * coeffs.c);
	if (discriminant < 0)
		return (0);
	t_body = (-coeffs.b - sqrt(discriminant)) / (2.0 * coeffs.a);
	// Check if the intersection point is within the cylinder's height
	if (t_body > 0) 
	{
		t_vector intersection = vector_add(ray.origin, vector_scale(ray.direction, t_body));
		double y = vector_dot(vector_subtract(intersection, cylinder.pos), cylinder.dir);
		if (y < 0 || y > cylinder.height)
			t_body = INFINITY;
	} 
	else
		t_body = INFINITY;

	// Calculate cap intersections
	v_caps[0] = vector_add(cylinder.pos, vector_scale(cylinder.dir, 0.5 * cylinder.height));
	v_caps[1] = vector_subtract(cylinder.pos, vector_scale(cylinder.dir, 0.5 * cylinder.height));
	for (int i = 0; i < 2; i++)
	{
		t_caps[i] = vector_dot(vector_subtract(v_caps[i], ray.origin), cylinder.dir) / vector_dot(ray.direction, cylinder.dir);
		if (t_caps[i] > 0) {
			t_vector p = vector_add(ray.origin, vector_scale(ray.direction, t_caps[i]));
			double r = vector_dot(vector_subtract(p, v_caps[i]), vector_subtract(p, v_caps[i]));
			if (r > cylinder.radius * cylinder.radius)
				t_caps[i] = INFINITY;
		}
		else 
		{
			t_caps[i] = INFINITY;
		}
	}

	// Find the smallest positive t
	*t = fmin(t_body, fmin(t_caps[0], t_caps[1]));
	return (*t != INFINITY);
}
