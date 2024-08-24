#include <miniRT.h>

mlx_image_t	*make_checkerboard(t_color color)
{
	mlx_image_t	*checkerboard;
	t_color		inverted;
	int			i;
	int			j;

	inverted = color_subtract(color_create(1, 1, 1), color);
	checkerboard = mlx_new_image(rtx()->mlx, 256, 256);
	if (!checkerboard)
		error(E_MLX, NULL);
	i = -1;
	while (++i < 256)
	{
		j = -1;
		while (++j < 256)
		{
			if ((i / 32 + j / 32) % 2 == 0)
				mlx_put_pixel(checkerboard, i, j, color_to_int(inverted));
			else
				mlx_put_pixel(checkerboard, i, j, color_to_int(color));
		}
	}
	return (checkerboard);
}
