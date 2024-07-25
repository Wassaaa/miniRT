#include <miniRT.h>

#define MAX_DEPTH 10
#define AABB_LINE_THICKNESS 0.05

static const t_rgba depth_colors[MAX_DEPTH] = {
	RGBA(COLOR_GREEN, 1),		// Green
	RGBA(COLOR_BLUE, 1),		// Blue
	RGBA(COLOR_RED, 1),		// Red
	RGBA(COLOR_YELLOW, 1),	// Yellow
	RGBA(COLOR_MAGENTA, 1),	// Magenta
	RGBA(COLOR_CYAN, 1),		// Cyan
	RGBA(COLOR_ORANGE, 1),	// Orange
	RGBA(COLOR_PURPLE, 1),	// Purple
	RGBA(COLOR_LIME, 1),		// Lime
	RGBA(COLOR_GRAY, 1),		// Gray
};

typedef struct s_aabb_line
{
	t_vector	start;
	t_vector	end;
	t_rgba		color;
	t_vector	direction;
	double		length_squared;
	double		inv_length_squared;
}	t_aabb_line;

void generate_aabb_lines(t_bvh *node, int depth, t_list **lines);
void add_aabb_line(t_list **lines, t_vector start, t_vector end, t_rgba color);
bool intersect_aabb_line(t_ray ray, t_aabb_line *line, double *t);
int trace_ray_with_aabb(t_ray ray, t_list *aabb_lines);
void render_scene_with_aabb(void);

void generate_aabb_lines(t_bvh *node, int depth, t_list **lines)
{
	if (!node)
		return;

	t_rgba color = depth_colors[depth % MAX_DEPTH];
	t_vector corners[8] = {
		{node->box.min.x, node->box.min.y, node->box.min.z}, // 0
		{node->box.max.x, node->box.min.y, node->box.min.z}, // 1
		{node->box.min.x, node->box.max.y, node->box.min.z}, // 2
		{node->box.max.x, node->box.max.y, node->box.min.z}, // 3
		{node->box.min.x, node->box.min.y, node->box.max.z}, // 4
		{node->box.max.x, node->box.min.y, node->box.max.z}, // 5
		{node->box.min.x, node->box.max.y, node->box.max.z}, // 6
		{node->box.max.x, node->box.max.y, node->box.max.z}  // 7
	};

	// Front face
	add_aabb_line(lines, corners[0], corners[1], color);
	add_aabb_line(lines, corners[1], corners[3], color);
	add_aabb_line(lines, corners[3], corners[2], color);
	add_aabb_line(lines, corners[2], corners[0], color);

	// Back face
	add_aabb_line(lines, corners[4], corners[5], color);
	add_aabb_line(lines, corners[5], corners[7], color);
	add_aabb_line(lines, corners[7], corners[6], color);
	add_aabb_line(lines, corners[6], corners[4], color);

	// Connecting edges
	add_aabb_line(lines, corners[0], corners[4], color);
	add_aabb_line(lines, corners[1], corners[5], color);
	add_aabb_line(lines, corners[2], corners[6], color);
	add_aabb_line(lines, corners[3], corners[7], color);

	// printf("AABB at depth %d:\n", depth);
	// printf("  Min: (%.2f, %.2f, %.2f)\n", node->box.min.x, node->box.min.y, node->box.min.z);
	// printf("  Max: (%.2f, %.2f, %.2f)\n", node->box.max.x, node->box.max.y, node->box.max.z);

	// Recursively generate lines for child nodes
	generate_aabb_lines(node->left, depth + 1, lines);
	generate_aabb_lines(node->right, depth + 1, lines);
}

void add_aabb_line(t_list **lines, t_vector start, t_vector end, t_rgba color)
{
	t_aabb_line *line = malloc(sizeof(t_aabb_line));
	line->start = start;
	line->end = end;
	line->color = color;
	line->direction = vector_subtract(end, start);
	line->length_squared = vector_dot(line->direction, line->direction);
	line->inv_length_squared = 1.0 / line->length_squared;
	ft_lstadd_back(lines, ft_lstnew(line));
	// printf("  Line: (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)\n", 
	// 	start.x, start.y, start.z, end.x, end.y, end.z);
}

/*
AABB edge: P(s) = P0 + s * u
RAY: Q(t) = Q0 + t * v
Vector between points on the lines:
w(s,t) = P(s) - Q(t) = (P0 + su) - (Q0 + tv)
*/
bool intersect_aabb_line(t_ray ray, t_aabb_line *line, double *t)
{
	t_vector ray_to_line = vector_subtract(line->start, ray.origin);

	double	a = line->length_squared;
	double	b = vector_dot(line->direction, ray.direction);
	double	c = vector_dot(ray.direction, ray.direction);
	double	d = vector_dot(line->direction, ray_to_line);
	double	e = vector_dot(ray.direction, ray_to_line);

	double	denom = a * c - b * b;
	if (fabs(denom) < 1e-6)  // Ray is parallel to the line
		return false;
	double	inv_denom = 1.0 / denom;
	double	line_t = (b * e - c * d) * inv_denom;
	double	ray_t = (a * e - b * d) * inv_denom;

	if (line_t < 0)
		line_t = 0;
	if (line_t > 1)
		line_t = 1;

	t_vector closest_point_on_line = vector_add(line->start, vector_scale(line->direction, line_t));
	t_vector closest_point_on_ray = vector_add(ray.origin, vector_scale(ray.direction, ray_t));

	double distance_sq = vector_dot(
		vector_subtract(closest_point_on_line, closest_point_on_ray),
		vector_subtract(closest_point_on_line, closest_point_on_ray)
	);

	// static double closest = INFINITY;
	// if (distance < closest)
	// {
	// 	closest = distance;
	// 	printf("New closest distance: %.2f\n", distance);
	// }

	if (distance_sq <= AABB_LINE_THICKNESS * AABB_LINE_THICKNESS)
	{
		*t = ray_t;
		return (true);
	}

	return (false);
}

int trace_ray_with_aabb(t_ray ray, t_list *aabb_lines)
{
	t_intersection t = {INFINITY, NULL, false};
	double line_t;

	t.hit = intersect_bvh(rtx()->bvh, ray, &t);
	int color = t.hit ? get_pixel_color(ray, t) : TEST_BG;

	// Check intersections with AABB lines
	t_list *current = aabb_lines;
	while (current)
	{
		t_aabb_line *line = (t_aabb_line *)current->content;
		if (intersect_aabb_line(ray, line, &line_t) && line_t < t.distance)
		{
			color = get_rgba(line->color, 1.0);
			break;
		}
		current = current->next;
	}

	return color;
}

void render_scene_with_aabb(void)
{
	t_ray ray;
	int color;
	int x, y;
	t_list *aabb_lines = NULL;
	int intersections = 0;

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

	// Free AABB lines
	// printf("\e[8;1Hintersections [%d]\e[K\n", intersections);
	ft_lstclear(&aabb_lines, free);
}