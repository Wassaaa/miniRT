#include <miniRT.h>

void	error(void)
{
	perror("ERROR\n");
	perror(mlx_strerror(mlx_errno));
	mlx_terminate(rtx()->mlx);
	exit(1);
}

void	render(void)
{
	render_multi_threaded();
	// render_scene();
}

int	main(int argc, char *argv[])
{
	/*
	parse_input(argv); will move before init_rtx() when the praser is made independent of mlx
	*/
	if (argc != 2)
		error_exit("Wrong argument number!");
	ft_bzero(rtx(), sizeof(t_rtx));
	init_rtx();
	parse_input(argv);
	setup_scene();
	render();
	mlx_key_hook(rtx()->mlx, key_hook, rtx());
	mlx_loop_hook(rtx()->mlx, loop_hook, rtx());
	mlx_resize_hook(rtx()->mlx, resize_hook, rtx());
	mlx_loop(rtx()->mlx);
	mlx_terminate(rtx()->mlx);
	// 	//free_all function or something
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		error_exit("Wrong argument number!");
// ft_bzero(rtx(), sizeof(t_rtx));
// 	parse_input(argv);
// 	setup_scene();
// 	//free_all function or something
// 	return (0);
// }
