#include <miniRT.h>

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

void	free_shape(void *content);

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error_exit(ERR_ARG_COUNT);
	ft_bzero(rtx(), sizeof(t_rtx));
	parse_input(argv);
	// setup_scene();
	// free_all function or something
	ft_lstclear(&rtx()->shapes, free_shape);
	ft_lstclear(&rtx()->unbound, free_shape);
	ft_lstclear(&rtx()->lights, free);
	error(E_NOPE, NULL);
	return (0);
}
