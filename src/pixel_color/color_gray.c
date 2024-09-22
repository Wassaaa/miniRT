/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_gray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:15:10 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:15:11 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h> 

static int32_t	get_rgba_gray(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	int32_t	gray;

	gray = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
	return (gray << 24 | gray << 16 | gray << 8 | a);
}

static int32_t	get_pixel_gray(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*start;

	start = img->pixels + (y * img->width + x) * 4;
	return (get_rgba_gray(start[0], start[1], start[2], start[3]));
}

mlx_image_t	*mlx_image_gray(mlx_t *mlx, mlx_image_t *image)
{
	mlx_image_t	*gray;
	uint32_t	color_gray;
	uint32_t	x;
	uint32_t	y;

	gray = mlx_new_image(mlx, image->width, image->height);
	if (!gray)
		return (NULL);
	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			color_gray = get_pixel_gray(image, x, y);
			mlx_put_pixel(gray, x, y, color_gray);
			x++;
		}
		y++;
	}
	return (gray);
}
