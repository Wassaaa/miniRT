/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:28 by jtu               #+#    #+#             */
/*   Updated: 2024/08/30 16:58:29 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	start_mlx(int width, int height)
{
	rtx()->width = width;
	rtx()->height = height;
	if (!rtx()->mlx)
	{
		rtx()->mlx = mlx_init(width, height, "miniRT", 1);
		if (!rtx()->mlx)
			error(E_MLX, NULL);
	}
	rtx()->img = mlx_new_image(rtx()->mlx, width, height);
	if (!rtx()->img)
		error(E_MLX, NULL);
}

void	rebuild_bvh(void)
{
	if (rtx()->bvh)
		free_bvh(&rtx()->bvh);
	if (!rtx()->shapes)
		return ;
	rtx()->bvh = bvh(rtx()->shapes);
	if (!rtx()->bvh)
		error(E_MEM, NULL);
}

static mlx_image_t	*safe_mlx_put_string(mlx_t *mlx, char *str)
{
	mlx_image_t	*img;

	img = mlx_put_string(mlx, str, 0, 0);
	if (!img)
		error(E_MLX, NULL);
	img->enabled = false;
	return (img);
}

void	init_ui(void)
{
	t_rtx	*rtx_data;

	rtx_data = rtx();
	rtx_data->ui[SPHERE] = safe_mlx_put_string(rtx_data->mlx, "SPHERE");
	rtx_data->ui[CYLINDER] = safe_mlx_put_string(rtx_data->mlx, "CYLINDER");
	rtx_data->ui[CONE] = safe_mlx_put_string(rtx_data->mlx, "CONE");
	rtx_data->ui[PLANE] = safe_mlx_put_string(rtx_data->mlx, "PLANE");
	rtx_data->ui[LIGHT] = safe_mlx_put_string(rtx_data->mlx, "LIGHT");
	change_target();
}

void	init_rtx(void)
{
	start_mlx(WIDTH, HEIGHT);
	rtx()->seed = (unsigned int)(mlx_get_time() * 1000000);
	if (mlx_image_to_window(rtx()->mlx, rtx()->img, 0, 0) == -1)
		error(E_MLX, NULL);
	init_ui();
}
