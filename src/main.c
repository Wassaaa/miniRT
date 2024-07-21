#include <miniRT.h>

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}

void	start_mlx(void)
{
	rtx()->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 0);
	rtx()->width = WIDTH;
	rtx()->height = HEIGHT;
}

int	main(void)
{
	start_mlx();
	mlx_loop(rtx()->mlx);
}
