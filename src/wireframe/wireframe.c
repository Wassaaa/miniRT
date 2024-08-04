#include <miniRT.h>

t_bvh	*make_wireframe(t_bvh *shapes_bvh)
{
	t_list	*wireframe;

	wireframe = NULL;
	generate_aabb_lines(shapes_bvh, 0, &wireframe);
	return (bvh(wireframe));
}