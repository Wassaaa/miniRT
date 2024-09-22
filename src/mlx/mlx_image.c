/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:43 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:17:44 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

mlx_image_t	*png_to_image(mlx_t *mlx, char *path, bool to_grayscale)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	mlx_image_t		*gray;

	if (!path)
		return (NULL);
	texture = mlx_load_png(path);
	if (!texture)
		error(E_MLX, NULL);
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		mlx_delete_texture(texture);
		error(E_MLX, NULL);
	}
	mlx_delete_texture(texture);
	if (to_grayscale)
	{
		gray = mlx_image_gray(mlx, image);
		if (!gray)
			error(E_MLX, NULL);
		mlx_delete_image(mlx, image);
		return (gray);
	}
	return (image);
}
