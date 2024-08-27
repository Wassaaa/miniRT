/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:38 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:17:39 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	render(void)
{
	render_multi_threaded();
	// render_scene();
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error(E_PARSER, "Wrong argument number!");
	ft_bzero(rtx(), sizeof(t_rtx));
	parse_input(argv);
	init_rtx();
	setup_scene();
	render();
	mlx_key_hook(rtx()->mlx, key_hook, rtx());
	mlx_loop_hook(rtx()->mlx, loop_hook, rtx());
	mlx_resize_hook(rtx()->mlx, resize_hook, rtx());
	mlx_loop(rtx()->mlx);
	error(E_NOPE, NULL);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		error_exit(ERR_ARG_COUNT);
// 	ft_bzero(rtx(), sizeof(t_rtx));
// 	parse_input(argv);
// 	// setup_scene();
// 	error(E_NOPE, NULL);
// 	return (0);
// }
