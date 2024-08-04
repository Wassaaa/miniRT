#include <miniRT.h>

/*
move an object based on current camera direction
*/
void	translate_vector(t_vector *object, t_direction dir)
{
	t_camera	*camera;

	camera = &(rtx()->scene->camera);
	if (dir == UP)
		*object = vector_add(
			*object, vector_scale(camera->up, MOVE_SPEED));
	if (dir == RIGHT)
		*object = vector_add(
			*object, vector_scale(camera->right, MOVE_SPEED));
	if (dir == DOWN)
		*object = vector_add(
			*object, vector_scale(camera->up, -MOVE_SPEED));
	if (dir == LEFT)
		*object = vector_add(
			*object, vector_scale(camera->right, -MOVE_SPEED));
	if (dir == FORWARD)
		*object = vector_add(
			*object, vector_scale(camera->dir, MOVE_SPEED));
	if (dir == BACK)
		*object = vector_add(
			*object, vector_scale(camera->dir, -MOVE_SPEED));
}

void	move_shapes(t_direction dir)
{
	t_list	*shapes;
	t_shape *shape;

	shapes = rtx()->shapes;
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		translate_vector(&shape->pos, dir);
		shape->box = shape->boxfunc(shape);
		shapes = shapes->next;
	}
	rtx()->bvh = bvh(rtx()->shapes);
}
