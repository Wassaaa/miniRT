#include <miniRT.h>

/*
calculate right and up vectors based on current camera dir and WORLD_UP
WORLD_UP x CAMERA_FORWARD = CAM_RIGHT
CAMERA_FORWARD x CAM_RIGHT = CAM_UP
*/
void	fix_camera(void)
{
	t_scene	*scene;

	scene = rtx()->scene;
	scene->camera.right = vector_cross(WORLD_UP, scene->camera.dir);
	scene->camera.right = vector_normalize(scene->camera.right);
	scene->camera.up = vector_cross(scene->camera.dir, scene->camera.right);
	scene->camera.up = vector_normalize(scene->camera.up);
}

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}
