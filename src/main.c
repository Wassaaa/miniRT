#include <miniRT.h>

void	free_shape(void *content)
{
	t_shape	*shape;

	shape = (t_shape *)content;
	if (shape->texture)
		mlx_delete_image(rtx()->mlx, shape->texture);
	if (shape->bump)
		mlx_delete_image(rtx()->mlx, shape->bump);
	if (shape->checkerboard)
		mlx_delete_image(rtx()->mlx, shape->checkerboard);
	free(shape);
}

void	error(void)
{
	perror("ERROR\n");
	// perror(mlx_strerror(mlx_errno));
	free_bvh(&rtx()->bvh);
	free_bvh(&rtx()->wireframe_bvh);
	//take care of all wireframe lists freeing
	ft_lstclear(&rtx()->shapes, free_shape);
	ft_lstclear(&rtx()->unbound, free_shape);
	ft_lstclear(&rtx()->lights, free);
	if (rtx()->mlx)
		mlx_terminate(rtx()->mlx);
	exit(1);
}

void	render(void)
{
	render_multi_threaded();
	// render_scene();
}

// int	main(int argc, char *argv[])
// {
// 	/*
// 	parse_input(argv); will move before init_rtx() when the praser is made independent of mlx
// 	*/
// 	if (argc != 2)
// 		error_exit("Wrong argument number!");
// 	ft_bzero(rtx(), sizeof(t_rtx));
// 	parse_input(argv);
// 	init_rtx();
// 	setup_scene();
// 	render();
// 	mlx_key_hook(rtx()->mlx, key_hook, rtx());
// 	mlx_loop_hook(rtx()->mlx, loop_hook, rtx());
// 	mlx_resize_hook(rtx()->mlx, resize_hook, rtx());
// 	mlx_loop(rtx()->mlx);
// 	mlx_terminate(rtx()->mlx);
// 	// 	//free_all function or something
// 	return (0);
// }

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error_exit("Wrong argument number!");
	ft_bzero(rtx(), sizeof(t_rtx));
	parse_input(argv);
	// setup_scene();
	// free_all function or something
	// free_bvh(&rtx()->bvh);
	// free_bvh(&rtx()->wireframe_bvh);
	// //take care of all wireframe lists freeing
	// ft_lstclear(&rtx()->shapes, free_shape);
	// ft_lstclear(&rtx()->unbound, free_shape);
	// ft_lstclear(&rtx()->lights, free);
	// if (rtx()->mlx)
	// 	mlx_terminate(rtx()->mlx);
	error_exit("NULL");
	return (0);
}
