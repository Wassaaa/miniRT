#include <miniRT.h>
#include <wireframe.h>

static int trace_ray_with_aabb(t_ray ray, t_list *aabb_lines)
{
	t_intersection t = {INFINITY, NULL, false, VV, VV};
	double line_t;

	t.hit = intersect_bvh(rtx()->bvh, ray, &t);
	int color = t.hit ? get_pixel_color(ray, t) : TEST_BG;

	// Check intersections with AABB lines
	t_list *current = aabb_lines;
	while (current)
	{
		t_shape *line = (t_shape *)current->content;
		if (intersect_aabb_line(ray, line, &line_t) && line_t > 0 && line_t < t.distance)
		{
			color = get_rgba(line->color, 1.0);
			break;
		}
		current = current->next;
	}

	return color;
}

void	render_scene_with_aabb(void)
{
	t_ray	ray;
	int		color;
	int		x;
	int		y;
	t_list	*aabb_lines = NULL;
	int		intersections = 0;

	// Generate AABB wireframe lines
	generate_aabb_lines(rtx()->bvh, 0, &aabb_lines);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(x, y);
			color = trace_ray_with_aabb(ray, aabb_lines);
			if (color != TEST_BG)
				intersections++;
			mlx_put_pixel(rtx()->img, x, y, color);
			x++;
		}
		y++;
	}
	ft_lstclear(&aabb_lines, free);
}
