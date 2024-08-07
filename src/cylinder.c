#include <miniRT.h>

t_shape	*make_cylinder(t_vector pos, t_vector dir, double diameter, double height, t_color color)
{
	t_shape	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_shape));
	cylinder->type = CYLINDER;
	cylinder->pos = pos;
	cylinder->dir = check_dir(dir);
	cylinder->diameter = diameter;
	cylinder->radius = diameter * 0.5;
	cylinder->height = height;
	cylinder->half_height = height / 2;
	cylinder->color = color_from_int(color.r, color.g, color.b);
	cylinder->boxfunc = box_cylinder;
	cylinder->box = cylinder->boxfunc(cylinder);
	cylinder->shine = SHINE;
	cylinder->reflectivity = 0.0;
	cylinder->image = rtx()->checkerboard;
	return (cylinder);
}

t_vector	check_dir(t_vector dir)
{
	if (dir.x > 1 || dir.y > 1 || dir.z > 1 || dir.x < -1 || dir.y < -1 || dir.z < -1)
		printf("Wrong direction input");
	if (vector_length(dir) != 1)
	{
		printf("Dirction is not normalized");
		return (vector_normalize(dir));
	}
	return (dir);
}


t_quadratic_coeffs	quadratic_coeffs_cylinder(t_ray ray, t_shape shape)
{
	t_quadratic_coeffs	coeffs;
	t_vector			oc;

	oc = vector_subtract(ray.origin, shape.pos);
	coeffs.a = vector_dot(ray.direction, ray.direction)
		- pow(vector_dot(ray.direction, shape.dir), 2);
	coeffs.b = 2 * (vector_dot(ray.direction, oc)
		- vector_dot(ray.direction, shape.dir) * vector_dot(oc, shape.dir));
	coeffs.c = vector_dot(oc, oc) - pow(vector_dot(oc, shape.dir), 2)
		- shape.radius * shape.radius;
	return (coeffs);
}

double	intersect_cylinder_caps(t_ray ray, t_shape cylinder)
{
	t_vector	v_caps[2];
	double		t_caps[2];
	t_vector	v;
	double		r_squared;
	int			i;

	i = -1;
	while (++i < 2)
	{
		v_caps[i] = vector_add(cylinder.pos, vector_scale(cylinder.dir,
					(i * 2 - 1) * 0.5 * cylinder.height));
		t_caps[i] = vector_dot(vector_subtract(v_caps[i], ray.origin),
				cylinder.dir) / vector_dot(ray.direction, cylinder.dir);
		if (t_caps[i] > 0)
		{
			v = vector_subtract(vector_add(ray.origin,
						vector_scale(ray.direction, t_caps[i])), v_caps[i]);
			r_squared = vector_dot(v, v) - pow(vector_dot(v, cylinder.dir), 2);
			if (r_squared > cylinder.radius * cylinder.radius)
				t_caps[i] = INFINITY;
		}
		else
			t_caps[i] = INFINITY;
	}
	return (fmin(t_caps[0], t_caps[1]));
}

int	intersect_cylinder(t_ray ray, t_shape cylinder, double *t)
{
	t_quadratic_coeffs	coeffs;
	double				discriminant;
	t_vector			intersection;
	double				t_body;
	double				y;

	coeffs = quadratic_coeffs_cylinder(ray, cylinder);
	discriminant = (coeffs.b * coeffs.b) - (4 * coeffs.a * coeffs.c);
	if (discriminant < 0)
		return (0);
	t_body = get_valid_t(&coeffs, &discriminant);
	if (t_body > 0)
	{
		intersection = vector_add(ray.origin,
				vector_scale(ray.direction, t_body));
		y = vector_dot(vector_subtract(intersection, cylinder.pos),
				cylinder.dir);
		if (fabs(y) > cylinder.height / 2)
			t_body = INFINITY;
	}
	else
		t_body = INFINITY;
	*t = fmin(t_body, intersect_cylinder_caps(ray, cylinder));
	return (*t != INFINITY);
}
