#include <miniRT.h>

t_shape	*make_cone(t_vector pos, t_vector dir, double diameter, double height, t_color color)
{
	t_shape			*cone;
	// mlx_texture_t	*texture;

	cone = ft_calloc(1, sizeof(t_shape));
	cone->type = CONE;
	cone->pos = pos;
	cone->dir = check_dir(vector_scale(dir, -1)); 
	cone->diameter = diameter;
	cone->radius = diameter * 0.5;
	cone->height = height;
	cone->color = color_from_int(color.r, color.g, color.b);
	cone->boxfunc = box_cone;
	cone->box = cone->boxfunc(cone);
	cone->half_angle = atan(cone->radius / cone->height);
	cone->tan_half_angle = tan(cone->half_angle);
	cone->cos_theta = 1.0 / sqrt(1 + cone->tan_half_angle * cone->tan_half_angle);
	cone->sin_theta = cone->tan_half_angle * cone->cos_theta;
	cone->shine = SHINE;
	cone->reflectivity = 0.0;
	cone->image = rtx()->checkerboard;
	// texture = mlx_load_png("textures/hive.png");
	// cone->image = mlx_texture_to_image(rtx()->mlx, texture);
	// mlx_delete_texture(texture);
	return (cone);
}

t_quadratic_coeffs	quadratic_coeffs_cone(t_ray ray, t_shape *cone)
{
	t_quadratic_coeffs	coeffs;
	t_vector			oc;
	double				k;

	oc = vector_subtract(ray.origin, cone->pos);
	k = pow(cone->radius / cone->height, 2);
	coeffs.a = vector_dot(ray.direction, ray.direction) -
		(1 + k) * pow(vector_dot(ray.direction, cone->dir), 2);
	coeffs.b = 2 * (vector_dot(ray.direction, oc) -
		(1 + k) * vector_dot(ray.direction, cone->dir) * vector_dot(oc, cone->dir));
	coeffs.c = vector_dot(oc, oc) -
		(1 + k) * pow(vector_dot(oc, cone->dir), 2);
	return (coeffs);
}

double	intersect_cone_base(t_ray ray, t_shape *cone)
{
	t_vector	base_center;
	double		t;
	t_vector	p;

	base_center = vector_subtract(cone->pos, vector_scale(cone->dir, -cone->height));
	t = vector_dot(vector_subtract(base_center, ray.origin), cone->dir) / 
		vector_dot(ray.direction, cone->dir);
	if (t > 0)
	{
		p = vector_subtract(vector_add(ray.origin, vector_scale(ray.direction, t)), 
			base_center);
		if (vector_dot(p, p) <= cone->radius * cone->radius)
			return (t);
	}
	return (INFINITY);
}

int	intersect_cone(t_ray ray, t_shape *cone, double *t)
{
	t_quadratic_coeffs	coeffs;
	double				discriminant;
	t_vector			intersection;
	double				t_body;
	double				y;

	coeffs = quadratic_coeffs_cone(ray, cone);
	discriminant = (coeffs.b * coeffs.b) - (4 * coeffs.a * coeffs.c);
	if (discriminant < 0)
		return (0);
	t_body = (-coeffs.b - sqrt(discriminant)) / (2.0 * coeffs.a);
	if (t_body > 0)
	{
		intersection = vector_add(ray.origin, vector_scale(ray.direction, t_body));
		y = vector_dot(vector_subtract(intersection, cone->pos), cone->dir);
		if (y < 0 || y > cone->height)
			t_body = INFINITY;
	}
	else
		t_body = INFINITY;
	*t = fmin(t_body, intersect_cone_base(ray, cone));
	return (*t != INFINITY);
}
