#include <miniRT.h>

bool	check_unbound(t_ray *ray, t_hit *hit)
{
	t_list	*unbound;
	t_shape	*shape;
	double	distance;

	unbound = rtx()->unbound;
	while (unbound)
	{
		shape = (t_shape *)unbound->content;
		if (shape->type == PLANE)
		{
			if (intersect_plane(*ray, *shape, &distance) && distance < hit->distance)
			{
				if (distance > 0.001 && distance < hit->distance)
				{
					hit->distance = distance;
					hit->shape = shape;
					hit->hit = true;
				}
			}
		}
		unbound = unbound->next;
	}
	return (hit->hit);
}

void	ft_swap(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void get_valid_t(double t[2], t_quadratic_coeffs *coeffs, double *discriminant)
{
	t[0] = (-coeffs->b - sqrt(*discriminant)) / (2.0 * coeffs->a);
	t[1] = (-coeffs->b + sqrt(*discriminant)) / (2.0 * coeffs->a);
	if (t[1] < t[0] && t[1] > 0)
		ft_swap(&t[0], &t[1]);
}

bool	intersect(t_shape *shape, t_ray ray, double *t)
{
	bool	hit;

	hit = false;
	if (shape->type == SPHERE)
		hit = intersect_sphere(ray, shape, t);
	else if (shape->type == CYLINDER)
		hit = intersect_cylinder(ray, *shape, t);
	else if (shape->type == CONE)
		hit = intersect_cone(&ray, shape, t);
	else if (shape->type == LINE || shape->type == WIREFRAME)
		hit = intersect_aabb_line(ray, shape, t);
	if (*t < 0)
		return (false);
	return (hit && *t > 0);
}