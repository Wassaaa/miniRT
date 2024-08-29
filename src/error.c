/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:11 by jtu               #+#    #+#             */
/*   Updated: 2024/08/30 02:19:06 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	clear_mlx(void)
{
	int	i;

	i = 0;
	mlx_delete_image(rtx()->mlx, rtx()->img);
	while (i < SHAPE_NUM)
	{
		if (rtx()->ui[i])
			mlx_delete_image(rtx()->mlx, rtx()->ui[i]);
		i++;
	}
	mlx_terminate(rtx()->mlx);
}

static void	free_shape(void *content)
{
	t_shape	*shape;

	shape = (t_shape *)content;
	if (shape->texture)
		mlx_delete_image(rtx()->mlx, shape->texture);
	if (shape->bump)
		mlx_delete_image(rtx()->mlx, shape->bump);
	if (shape->checkerboard)
		mlx_delete_image(rtx()->mlx, shape->checkerboard);
	if (shape->bmp_path)
		free(shape->bmp_path);
	if (shape->tex_path)
		free(shape->tex_path);
	free(shape);
}

static void	error_exit(const char *err_msg)
{
	if (err_msg)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd((char *)err_msg, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (rtx()->mlx)
		clear_mlx();
	exit(EXIT_SUCCESS);
}

void	error(t_err_type err, const char *msg)
{
	free_bvh(&rtx()->bvh);
	free_bvh(&rtx()->wireframe_bvh);
	ft_lstclear(&rtx()->shapes, free_shape);
	ft_lstclear(&rtx()->unbound, free_shape);
	ft_lstclear(&rtx()->lights, free);
	clear_lal();
	if (err == E_MLX)
		error_exit(mlx_strerror(mlx_errno));
	if (err == E_MEM)
		error_exit(strerror(errno));
	if (err == E_PARSER)
		error_exit(msg);
	error_exit(NULL);
}
