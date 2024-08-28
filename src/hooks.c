/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:15 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:32:23 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	key_hook(mlx_key_data_t keydata, void *data)
{
	double	build_time;

	build_time = mlx_get_time();
	(void)data;
	if (keys(keydata))
	{
		render();
		build_time = mlx_get_time() - build_time;
		printf("\e[3;1HLast step Frame [%.0fms]\e[K\n", build_time * 1000);
	}
}

void	resize(void)
{
	double	since_resize;

	if (rtx()->resize)
	{
		since_resize = mlx_get_time() - rtx()->resize_time;
		if (since_resize > RESIZE_TIME)
		{
			if (rtx()->img)
			{
				if (!mlx_resize_image(rtx()->img, rtx()->width, rtx()->height))
					error(E_MLX, NULL);
				ft_bzero(rtx()->img->pixels,
					rtx()->img->width * rtx()->img->height * sizeof(uint32_t));
				rtx()->resize = false;
				render();
			}
		}
	}
}

void	loop_hook(void *data)
{
	static int		fps = 1;
	static double	i = 0;
	t_camera		camera;
	t_rtx			*rtx;

	rtx = (t_rtx *)data;
	camera = rtx->camera;
	i += rtx->mlx->delta_time;
	fps++;
	if (i >= 1)
	{
		printf("\e[1;1Hfps [%d]\e[K\n", fps);
		i = 0;
		fps = 0;
	}
	resize();
	printf("\e[2;1HLast Frame [%.0fms]\e[K\n",
		rtx->mlx->delta_time * 1000);
	printf("\e[4;1HFOV [%.2f]\e[K\n",
		camera.fov);
	printf("\e[5;1HCamera position [{%.2f, %.2f, %.2f}]\e[K\n",
		camera.pos.x, camera.pos.y, camera.pos.z);
	printf("\e[6;1HCamera direction [{%.2f, %.2f, %.2f}]\e[K\n",
		camera.dir.x, camera.dir.y, camera.dir.z);
}

void	resize_hook(int32_t width, int32_t height, void *data)
{
	t_rtx	*rtx;

	rtx = data;
	rtx->width = width;
	rtx->height = height;
	rtx->resize_time = mlx_get_time();
	rtx->resize = true;
}
