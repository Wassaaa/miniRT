#include <miniRT.h>
#include <pthread.h>

#define NUM_THREADS 12
#define SSAA 4

typedef struct s_thread_data
{
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
}	t_thread_data;

t_color	super_sample(int x, int y)
{
	int				i;
	double			offset[2];
	t_color			pixel_color;
	t_ray			ray;
	unsigned int	seed;

	seed = time(NULL) ^ (unsigned int)pthread_self();
	pixel_color = color_create(0, 0, 0);
	i = 0;
	while (i++ < SSAA)
	{
		offset[0] = (double)rand_r(&seed) / RAND_MAX;
		offset[1] = (double)rand_r(&seed) / RAND_MAX;
		ray = generate_ray(x + offset[0], y + offset[1]);
		pixel_color = color_add(pixel_color, trace_ray(&ray));
	}
	return (pixel_color);
}

void	*sample_region(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	t_color			pixel_color;

	data = (t_thread_data *)arg;
	y = data->start_y;
	while (y < data->end_y)
	{
		x = data->start_x;
		while (x < data->end_x)
		{
			pixel_color = super_sample(x, y);
			pixel_color = color_scale(pixel_color, 1.0 / SSAA);
			mlx_put_pixel(rtx()->img, x, y, color_to_int(pixel_color));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	render_multi_threaded(void)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	data[NUM_THREADS];
	int				i;

	i = 0;
	while (i < NUM_THREADS)
	{
		data[i].start_x = 0;
		data[i].end_x = WIDTH;
		data[i].start_y = i * (HEIGHT / NUM_THREADS);
		data[i].end_y = (i + 1) * (HEIGHT / NUM_THREADS);
		pthread_create(&threads[i], NULL, sample_region, &data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}