#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>

typedef struct s_rtx
{
	int		width;
	int		height;
}	t_rtx;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_amb_light
{
	double	amb_light;
	t_rgb	rgb;
}	t_amb_light;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vector	pos;
	t_vector	dir;
	double		bright;
	t_rgb		rgb;
}	t_light;

typedef struct s_sphere
{
	t_vector	pos;
	double		diameter;
	t_rgb		color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	pos;
	t_vector	dir;
	t_rgb		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	pos;
	t_vector	dir;
	double		diameter;
	double		height;
	t_rgb		color;
	
}	t_cylinder;

#endif
