#include <miniRT.h>

void	scale_shape(t_list *node, double mult)
{
	t_shape	*shape;
	t_shape	*new_shape;

	shape = (t_shape *)node->content;
	if (shape->type == SPHERE)
		new_shape = make_sphere(shape->pos, shape->diameter * mult, shape->color);
	else if (shape->type == CYLINDER)
		new_shape = make_cylinder(shape->pos, shape->dir, shape->diameter * mult, shape->height * mult, shape->color);
	else if (shape->type == CONE)
		new_shape = make_cone(shape->pos, vector_scale(shape->dir, -1), shape->diameter * mult, shape->height * mult, shape->color);
	else
		return ;
	node->content = new_shape;
	if (shape->image)
		mlx_delete_image(rtx()->mlx, shape->image);
	free(shape);
}

void	scale(t_direction dir)
{
	double	mult;
	t_list	*shapes;
	t_shape	*shape;

	if (dir == UP)
		mult = 1.0 + SCALE_STEP;
	else
		mult = 1.0 - SCALE_STEP;
	shapes = rtx()->shapes;
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (shape->type == rtx()->target)
			scale_shape(shapes, mult);
		shapes = shapes->next;
	}
	if (rtx()->bvh)
		free_bvh(rtx()->bvh);
	rtx()->bvh = bvh(rtx()->shapes);
	if (!rtx()->bvh)
		error();
}
