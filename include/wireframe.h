#ifndef WIREFRAME_H
# define WIREFRAME_H

# include <miniRT.h>

# define MAX_DEPTH 10
# define AABB_LINE_THICKNESS 0.1
# define EPSILON 1e-6


static const t_rgba depth_colors[MAX_DEPTH] = {
	RGBA(COLOR_GREEN, 1),
	RGBA(COLOR_BLUE, 1),
	RGBA(COLOR_RED, 1),
	RGBA(COLOR_YELLOW, 1),
	RGBA(COLOR_MAGENTA, 1),
	RGBA(COLOR_CYAN, 1),
	RGBA(COLOR_ORANGE, 1),
	RGBA(COLOR_PURPLE, 1),
	RGBA(COLOR_LIME, 1),	
	RGBA(COLOR_GRAY, 1),	
};

typedef struct s_coeff
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	e;
}	t_coeff;

#endif